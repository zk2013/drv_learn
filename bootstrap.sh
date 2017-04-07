usage() {
	echo "Usage: $0 {install|uninstall}"
        exit 1
}

check_run_env() {
	trap "exiterror 'process interrupted'" SIGINT SIGTERM SIGKILL SIGSTOP SIGQUIT
	
	echo -e "Checking if we're running as root user"
	if [ `id -u` != 0 ]; then
			echo -e "Not running as root\n"
			exit 1
    	fi
}

install() {
	insmod fuck_net.ko
}

uninstall() {
	rmmod fuck_net.ko
}

if [ $# -lt  1 ] ; then 
	usage
fi
check_run_env

case "$1" in 
install)
	install
	;;
uninstall)
	uninstall
	;;
*)
	usage
	;;
esac


