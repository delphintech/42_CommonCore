#!/bin/bash

mysql_install_db
# lancement de MySQL
mysqld_safe &

# On attend que le server soit lancé
while ! mysqladmin ping --silent; do sleep 1; done

mysqladmin -u $DB_ROOT password $DB_ROOT_PWD

# Creation de la database
mysql -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;"

# Creation d'un user
mysql -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@'%' IDENTIFIED BY '${DB_USER_PWD}';"
# Allocation de tous les droits au user créé
mysql -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@'%' IDENTIFIED BY '${DB_USER_PWD}';"

# On rafraichit
mysql -e "FLUSH PRIVILEGES;"
# On eteint
mysqladmin -u $DB_ROOT -p$DB_ROOT_PWD shutdown
# On redémarre
exec mysqld_safe