FROM	debian:bullseye

# Install nginx and ssl for TLS certificate
RUN		apt-get update -y && apt-get upgrade -y && apt-get install -y php \
	php-common \
	php-zip \
	php7.4-fpm \
	php-mysql \
	mariadb-client \
	wget

RUN mkdir -p /run/php
RUN chmod 755 /run/php

# Get our config file for php-fpm & wordpress
COPY	./conf/www.conf /etc/php/7.4/fpm/pool.d/

# Get the script to setup wordpress
COPY	./tools/wp_setup.sh /usr/local/bin
RUN		chmod +x /usr/local/bin/wp_setup.sh

EXPOSE 9000

ENTRYPOINT ["/usr/local/bin/wp_setup.sh"]
