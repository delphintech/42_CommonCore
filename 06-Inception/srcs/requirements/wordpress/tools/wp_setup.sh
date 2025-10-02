#!/bin/bash

# Download WP-CLI
wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -P /usr/local/bin
chmod +x /usr/local/bin/wp-cli.phar
mv /usr/local/bin/wp-cli.phar /usr/local/bin/wp

# Attente de Mariadb
while ! mysqladmin -h mariadb -P 3306 ping --silent; do sleep 2; done

cd /var/www/html

if [ ! -f ./wp-config.php ]; then
	wp core download --allow-root
	wp config create --dbname=$DB_NAME --dbuser=$DB_USER --dbpass=$DB_USER_PWD --dbhost='mariadb' --allow-root
	wp core install --url='https://dabouab.42.fr' --title='Inception' --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PWD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
	wp theme install blocksy --activate --allow-root
	wp user create $WP_USER $WP_USER_EMAIL --user_pass=$WP_USER_PWD --allow-root
fi

# Give permission to nginx
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

#lance php-fpm
/usr/sbin/php-fpm7.4 -F