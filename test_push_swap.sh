#!/usr/bin/env bash

# correction sheet
# https://github.com/rizky/42-corrections/blob/master/push_swap.pdf

TIMEOUT=2
SIGSEG=139
SIGTIME=124
INT_MAX=2147483647
INT_MIN=-2147483648

R=$(tput setaf 1)
G=$(tput setaf 2)
Y=$(tput setaf 3)

U=$(tput smul)
N=$(tput sgr0)

function median() {
  arr=($(printf '%d\n' "${@}" | sort -n))
  nel=${#arr[@]}
  if (( $nel % 2 == 1 )); then     # Odd number of elements
    val="${arr[ $(($nel/2)) ]}"
  else                            # Even number of elements
    (( j=nel/2 ))
    (( k=j-1 ))
    (( val=(${arr[j]} + ${arr[k]})/2 ))
  fi
  echo $val
}

printf "
${U}[Tests]${N}
- ARG = 2 1 0\t\tmust have 2 or 3 instructions
- ARG = 1 5 2 4 3\tmust not have more then 12 instructions
- ARG = <5 random>\tmust not have more then 12 instructions
- ARG = <100 random>
\t700   : 5
\t900   : 4
\t1100  : 3
\t1300  : 2
\t1500  : 1
- ARG = <500 random>
\t5500  : 5
\t7000  : 4
\t8500  : 3
\t10000 : 2
\t11500 : 1
\n"

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [[ "${machine:0:7}" == "UNKNOWN" ]]; then
  printf "%-20s%s\n" "${R}Error${N}" "Script does not support ${unameOut}"
  exit 1
fi

# Get shuf program. Differs between mac and linux
shuf="shuf"
if [ "$machine" = "Mac" ]; then
  shuf="gshuf"
fi

# Make sure all programs to run the script are installed and available
required_programs=(
  "$shuf"
  "python3"
  "timeout"
)
for prog in "${required_programs[@]}"
do
  if ! "$prog" --version &> /dev/null; then
    printf "%-20s%s\n" "${R}Error${N}" "Script needs $prog to function properly"
    exit 1
  fi
done

# Compile push_swap and checker (if there) using Makefile
if [[ -f Makefile ]]; then
  printf "${U}[Makefile]${N}\n"
  make
  if [[ "$?" -ne 0 ]]; then
    printf "${R}Error: ${N}Makefile failed to compile\n"
    exit 1
  fi
  echo
else
  printf "${Y}Warning: ${N}No Makefile found. Looking for executable $PWD/push_swap.\n";
fi
if [[ ! -x push_swap ]]; then
  printf "${R}Error: ${N}No executable $PWD/push_swap found\n";
  exit 1
fi

CHECKER=""
printf "${U}[Checker]${N}\n"
if [[ ! -x checker ]]; then
  echo "No checker compiled with Makefile. Looking for checker_$machine".
  if [[ ! -f "bin/checker_$machine" ]]; then
    echo "No checker program found. Unable to Validate push_swap output."
    exit 1
  else
    CHECKER="$PWD/bin/checker_$machine"
  fi
else
  CHECKER="$PWD/checker"
fi
printf "Using checker %s\n" "$CHECKER"
echo

# INPUT VALIDATION
printf "${U}[Input validation]${N}\n"
# 1. No duplicates
# 2. Empty strings
# 3. INT_MAX | INT_MIN
inputs_invalid=(
  "1 2 3 1" "1 1 2 3" "1 2 2 3" "1 2 3 3"
  "''" "'' 1 2" "1 '' 2" "1 2 ''"
  "$((INT_MAX+1)) 1" "$((INT_MIN-1)) 1"
)
for input in "${inputs_invalid[@]}"
do
  output=$(timeout "$TIMEOUT" ./push_swap $input 2>&1)
  exit_code="$?"
  if [[ "$exit_code" -eq $SIGTIME ]]; then
    printf "%-40s%-40s\n" "$input" "${R}TIMEOUT${N}"
  elif [[ "$exit_code" -eq $SIGSEG ]]; then
    printf "%-40s%-40s\n" "$input" "${R}SEGFAULT${N}"
  else
    if [[ ! $exit_code -eq 1 ]]; then
      printf "%-40s%-40s%-40s\n" "[$input]" "${R}EXIT_CODE${N}" "$exit_code -> 1"
    elif [[ ! "$output" == "Error" ]]; then
      printf "%-40s%-40s%-40s\n" "[$input]" "${R}ERR_MSG${N}" "$output -> Error"
    else
      printf "%-40s%-40s\n" "[$input]" "${G}PASSED${N}"
    fi
  fi
done
inputs_valid=(
  "$INT_MAX 1" "$INT_MIN 1" "$INT_MAX $INT_MIN"
)
for input in "${inputs_valid[@]}"
do
  output=$(timeout "$TIMEOUT" ./push_swap $input 2>&1)
  exit_code="$?"
  if [[ "$exit_code" -eq $SIGTIME ]]; then
    printf "%-40s%-40s\n" "$input" "${R}TIMEOUT${N}"
  elif [[ "$exit_code" -eq $SIGSEG ]]; then
    printf "%-40s%-40s\n" "$input" "${R}SEGFAULT${N}"
  else
    if [[ ! $exit_code -eq 0 ]]; then
      printf "%-40s%-40s%-40s\n" "[$input]" "${R}EXIT_CODE${N}" "$exit_code -> 0"
    elif [[ "$output" == "Error" ]]; then
      printf "%-40s%-40s%-40s\n" "[$input]" "${R}ERR_MSG${N}" "$output -> sa"
    else
      printf "%-40s%-40s\n" "[$input]" "${G}PASSED${N}"
    fi
  fi
done
echo

# 4. Checker -> Valid operations
#if [[ -x checker ]]; then
#
#fi

# PERMUTATIONS
printf "${U}[Permutations]${N}\n"
perm_test_nums_start=(-3 -4 -5 -2 3 4 5)
perm_test_nums_end=(-1 -1 -1 2 1 1 1)
perm_test_nums_max=(3 12 12 12 3 12 12)
for test_num_idx in "${!perm_test_nums_start[@]}"
do
  s="$(echo -n $(seq "${perm_test_nums_start[test_num_idx]}" "${perm_test_nums_end[test_num_idx]}") | tr ' ' ',')"
  cmd="from itertools import permutations as p; print(','.join([' '.join([str(j) for j in i]) for i in p([$s])]))"
  IFS=',' read -r -a permutations <<< "$(python3 -c "$cmd")"

  idx=1
  max_instructions="${perm_test_nums_max[test_num_idx]}"
  failed=0; timeout=0; segfault=0;
  factorial=$(seq "${perm_test_nums_start[test_num_idx]}" "${perm_test_nums_end[test_num_idx]}" | wc -l | tr -d '[:space:]')
  max=$(python3 -c "from math import factorial; print(factorial($factorial))")
  for perm in "${permutations[@]}"; do
    output=$(timeout "$TIMEOUT" ./push_swap $perm)
    exit_code="$?"
    if [[ "$exit_code" -eq $SIGTIME ]]; then
      printf "%-40s%-40s%-40s\n" "[$idx/$max]" "${R}TIMEOUT${N}:" "[$perm]"
      timeout=$(($timeout+1))
    elif [[ "$exit_code" -eq $SIGSEG ]]; then
      printf "%-40s%-40s%-40s\n" "[$idx/$max]" "${R}SEGFAULT${N}:" "[$perm]"
      segfault=$(($segfault+1))
    else
      instructions=$(echo "$output" | wc -l | tr -d "[:space:]")
      checked="OK"
      if [[ -n "$output" ]]; then
        checked=$(echo "$output" | $CHECKER $perm)
      fi
      if [[ $instructions -gt $max_instructions ]]; then
        printf "%-40s%-40s%-40s%-40s\n" "[$idx/$max]" "${R}FAILED${N}:" "[$perm]" "-> $instructions instructions\n"
        failed=$(($failed+1))
      elif [[ "$checked" == "KO" ]]; then
        printf "%-40s%-40s%-40s%-40s\n" "[$idx/$max]" "${R}INVALID${N}:" "[$perm]" "-> $instructions instructions\n"
      elif [[ "$1" == "-v" ]] || [[ "$1" == "--verbose" ]]; then
        printf "%-40s%-40s%-40s%-40s\n" "[$idx/$max]" "${G}PASSSED${N}:" "[$perm]" "-> $instructions instructions\n"
      fi
    fi
    idx=$(($idx+1))
  done
  printf "%-30s" "${U}[$s]${N}"
  printf "%-25s%-25s" "${G}PASSED${N}: $((max-failed-timeout-segfault))" "${R}FAILED${N}: $failed"
  printf "%-25s%-25s\n" "${R}TIMEOUT${N}: $timeout" "${R}SEGFAULT${N}: $segfault"
done
echo

printf "${U}[Median]${N}\n"
for idx in {1..5}
do

  ins=()
  argsize=$(( 100*idx ));
  printf "%-20s%-40s" "[$idx]" "amount of random integers used: $argsize"

  for shufidx in {1..20}
  do
    args=$(for ((i=0;i<argsize;i+=1)); do $shuf -i 1-$INT_MAX -n 1 ; done)
    output=$(timeout $TIMEOUT ./push_swap $args 2>&1)
    exit_code="$?"

    if [[ "$output" == "Error" ]]; then
      printf "%-25s" "${R}Error in push_swap${N}"
      break
    elif [[ "$exit_code" -eq $SIGTIME ]]; then
      echo -e -n "\tTIMEOUT" && printf "TIMEOUT:\n%s" $args >> deepthought
      break
    elif [[ "$exit_code" -eq $SIGSEG ]]; then
      echo -e -n "\tSEGFAULT" && printf "SEGFAULT:\n%s" $args >> deepthought
      break
    else
      if [[ -z "$output" ]]; then
        instructions=0
      else
        checked="OK"
        if [[ -n "$output" ]]; then
          checked=$(echo "$output" | $CHECKER $args 2>&1)
        fi
        if [[ "$checked" == "Error" ]]; then
          printf "%-25s" "${R}Error in checker${N}"
          break
        elif [[ "$checked" == "KO" ]]; then
          printf "%-25s" "${R}KO${N}"
          printf "KO:\n%s\n" "$(echo "$args" | tr '\n' ' ')" >> deepthought
          echo
          break
        fi
        instructions=$(echo "$output" | wc -l | tr -d "[:space:]")
      fi
      ins+=("$instructions")
    fi
  done
  median=$(median $(printf '%s ' "${ins[@]}"))
  printf "%-10s\n" "median: $median"
done
