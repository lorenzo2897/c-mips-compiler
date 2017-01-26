# remote make with flex, bison, g++
# ###

USEPROXY=0

function scpr {
	if [ $USEPROXY == 1 ]; then
		scp -o "ProxyCommand=nc -X 5 -x 192.168.43.1:1337 %h %p" $@
	else
		scp $@
	fi
}

function sshr {
	if [ $USEPROXY == 1 ]; then
		ssh -o "ProxyCommand=nc -X 5 -x 192.168.43.1:1337 %h %p" $@
	else
		ssh $@
	fi
}

# #####################

function putc {
	scpr -r src/ silvestrix.org:lscc/
}

function makec {
	sshr silvestrix.org "cd lscc; make clean; make"
}

function getc {
	scpr -r silvestrix.org:lscc/bin/ linux/
}

# #####################

if [ -z $1 ]; then

	make clean

	# copy files to remote server
	echo -e "\033[0;31mput: Copying files to remote server\033[0m"
	putc

	# make
	echo -e "\033[0;31mmake: Making files\033[0m"
	makec

	# copy back
	echo -e "\033[0;31mget: Copying back\033[0m"
	getc

	echo -e "\033[0;31mDone.\033[0m"
	exit

fi

# #####################

if [ $1 == 'put' ]; then
	echo -e "\033[0;31mput: Copying files to remote server\033[0m"
	putc
	exit
fi

if [ $1 == 'putm' ]; then
	echo -e "\033[0;31mputm: Copying new makefile to remote server\033[0m"
	scpr makefile silvestrix.org:lscc/
	exit
fi

if [ $1 == 'make' ]; then
	echo -e "\033[0;31mmake: Making files\033[0m"
	makec
	exit
fi

if [ $1 == 'get' ]; then
	echo -e "\033[0;31mget: Copying back\033[0m"
	getc
	exit
fi
