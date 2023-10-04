#!/bin/bash

#~ A=123.456.678
#~ echo $A ${A} ${A%/*} ${A%%/*} ${A#*/} ${A##*/}


#~ tput init # > /dev/null

#!/bin/sh
#~ exit_handler() {
  #~ trap - EXIT
  #~ test -r "$TMPFILE" && rm -vf "$TMPFILE"
#~ }

#~ trap exit_handler EXIT HUP INT QUIT PIPE TERM

#~ echo -n "Create a file? "
#~ read YN
#~ if [ "$YN" = y ]; then
        #~ TMPFILE="`mktemp`"
        #~ echo "$TMPFILE"
        #~ ls -l "$TMPFILE"
#~ fi
#~ echo -n "Wait…"
#~ read
#~ echo "Done"

#~ tput clear
#~ echo "qwertyuiop[]\nasdfghjkl;'\nzxcvbnm,./\nienoifm       jsmhfiiur  khref"
#~ tput cup 10 1
#~ cat test.sh 

#~ lines < 0
#~ #####
#~ tput clear
#~ input=()
#~ i=0
#~ cnt=0
#~ while read A ; do
	#~ input[$i]=$A
	#~ i=$[$i+1]
	#~ cnt=$[$cnt+${#A}]
#~ done
#~ a=$(shuf -i 0-$[${#input[*]}-1])
#~ aa=()
#~ i=0
#~ for j in $a; do
	#~ aa[$i]=$(shuf -i 0-$[${#input[$j]}-1])
	#~ echo ${aa[$i]}
	#~ i=$[$i+1]
#~ done
#~ i=0
#~ while(( $cnt>0 )); do
	#~ i=0
	#~ while (( i<${#a} )); do
		#~ x=${a:$i:$[$i+1]}
		#~ if (( $x!='#' )); then
			#~ y=${aa[$i]:0:1}
			##~ tput cup $[$x+5] $y
			##~ printf "%c" ${input[x]:$y:$[$y+1]}
			#~ cnt=$[$cnt-1]
			#~ if (( ${#aa[$i]}==1 )); then
				#~ a[$i]=-1
				#~ echo $a
			#~ else
				#~ aa[$i]=${aa[$i]:1:${#aa[$i]}}
				#~ echo ${aa[$i]}
			#~ fi
		#~ fi
		#~ i=$[$i+2]
		#~ sleep $1
	#~ done
	#~ echo "==========================="
#~ done
#~ tput cup $[${#input[*]}+5] 0

#~ a=$(od -A n -t c -v)
#~ echo $a

#~ echo $#
#~ slp=0
#~ if (( $#==0 )); then
	#~ slp=0
#~ else
	#~ slp=$1
#~ fi
#~ sleep $slp
#~ IFS=$'\n'
#~ input=()
#~ i=0
#~ cnt=0
#~ while read A ; do
	#~ input[$i]=$A
	#~ ((i++))
	#~ ((cnt=cnt+${#A}))
#~ done
#~ tmp=$(shuf -i 0-$[${#input[*]}-1])
#~ a=()
#~ aa=()
#~ i=0
#~ for j in $tmp; do
	#~ aa[$i]=$(shuf -i 0-$[${#input[$j]}-1])
	#~ echo
	#~ ((a[i]=j))
	#~ ((i++))
#~ done
#~ i=0
#~ a="12 efg"
#~ a=${a% *}
#~ echo $((a))
