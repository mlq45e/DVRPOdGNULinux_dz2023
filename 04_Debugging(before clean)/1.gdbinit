set pagination off
b 20
run 1 12 > /dev/null
while (i<11)
	if (i%5==0)
		echo @@@ 
		p i
	end
	cont
end
cont
quit
