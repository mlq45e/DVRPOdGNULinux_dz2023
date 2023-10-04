IFS=$'\n'
slp=0
if (( $#==0 )); then
	slp=0
else
	slp=$1
fi
input=()
i=0
cnt=0
while read A ; do
	input[$i]=$A
	((i++))
	((cnt=cnt+${#A}))
done
tmp=$(shuf -i 0-$[${#input[*]}-1])
a=()
aa=()
i=0
for j in $tmp; do
	aa[$i]=$(shuf -i 0-$[${#input[$j]}-1])
	((a[i]=j))
	((i++))
done
i=0
tput clear
while (( $cnt>0 )); do
	i=0
	while (( i<${#a[*]} )); do
		x=${a[$i]}
		if (( $x!=-1 )); then
			yy=${aa[$i]% *}
			let y=$yy
			tput cup $x $y
			printf "%c" ${input[$x]:$y:1}
			((cnt--))
			aare=${aa[$i]#* }
			if (( ${#aare}!=${#aa[$i]} )); then
				aa[$i]=${aa[$i]#* }
			else
				a[$i]=-1
			fi
			sleep $slp
		fi
		((i++))
	done
done
tput cup $[${#input[*]}] 0
