set pagination off
b 26
set $cnt = 0
run -100 100 3 > /dev/null
while (i<98)
	if ($cnt>=28&&$cnt<=35)
		echo @@@
		p i
	end
	set $cnt = $cnt + 1
	cont
end
cont
quit
