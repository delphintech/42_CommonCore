FROM	debian:bullseye

# Install nginx and ssl for TLS certificate
RUN		apt-get update -y && apt-get upgrade -y && apt-get install -y mariadb-server

# Get our config file
RUN		rm -f /etc/mysql/mariadb.conf.d/50-server.cnf
COPY	./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Get the script to setup mysql
COPY	./tools/mariadb_start.sh /usr/local/bin
RUN		chmod +x /usr/local/bin/mariadb_start.sh

EXPOSE 3306

ENTRYPOINT ["/usr/local/bin/mariadb_start.sh"]