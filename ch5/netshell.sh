url="http://cs.nju.edu.cn"
looptime=0
loopcount=10
#echo $content
echo "$(date | cut -c 5-18)"
while [ $looptime -lt $loopcount ]
do
	content=$(GET $url)
	let "looptime=$looptime+1"
done
