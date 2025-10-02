exit 0
#Zombie process
ps -eo pid,ppid,stat,cmd | grep Z

#siege
time siege  -c250 -r250 http://127.0.0.1:8080/

#Log
tail -f log.txt

#top
top -H -p <pid>

#test
valgrind --leak-check=full  ./webserv ./YoupiBanane/youpi.conf
./ubuntu_tester http://127.0.0.1:8080

#test trace
netstat -an | grep 8080 #check if port is open
sudo strace -e trace=network -p <pid> #check if process is listening on port
sudo lsof -i -P -n | grep LISTEN #check if process is listening on port
lsof -p <pid> #check if process is listening on port
ss -s #check if process is listening on port
nc 127.0.0.1 8080 # nc for netcat, -z for scanning, -v for verbose, -n for numeric-only IP addresses

 #Profiling avec callgrind, cela cree un fichier callgrind.out.<pid>
 valgrind --tool=callgrind  ./webserv ./conf.d/defaultform.conf 
 #visualiser le profiling
 kcachegrind ./callgrind.out.<pid>

 #install siege
 rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
 brew install siege