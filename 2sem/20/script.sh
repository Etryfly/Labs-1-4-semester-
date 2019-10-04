#!/bin/bash
echo diff 1 2
diff 1 2
echo cmp 1 2
cmp 1 2
echo tail 2 -n 3
tail 2 -n 3
echo 'od -bc 1 | less'
od -bc 1 | less
echo head 2 -c 2
head 2 -c 2
echo 'du * -b'
du * -b
echo 'ls | grep s*'
ls | grep 's*'
echo sum 1
sum 1
echo file 1
file 1
echo df 1
df 1
echo 'touch file'
touch file
echo 'dd if=/dev/zero of=file bs=10M count=1'
dd if=/dev/zero of=file bs=10M count=1
echo split -b 1M file
split -b 1M file
echo wc 1
wc 1
echo 'cat 1 | tr e n'
cat 1 | tr e n
echo 'cut -d : -f1 c'
cut -d : -f1 c
echo 'tar -cvf 1.tar 1'
tar -cvf 1.tar 1
echo "echo "This is a test" | sed 's/test/another test/'"
echo "This is a test" | sed 's/test/another test/'
echo 'cat 1'
cat 1
echo 'sort 1'
sort 1
echo 'cat 1 | md5sum'
cat 1 | md5sum
