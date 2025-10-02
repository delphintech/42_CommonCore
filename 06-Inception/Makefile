all: 
	mkdir -p /home/dabouab/data/wordpress
	# chown -R www-data:www-data /home/dabouab/data/wordpress
	mkdir -p /home/dabouab/data/mariadb
	docker compose -f ./srcs/docker-compose.yml up

stop:
	docker compose -f ./srcs/docker-compose.yml down

terminal:
	@echo "Container name ?"; \
	read CONT; \
	docker exec -it $$CONT bash

clean:
	docker compose -f ./srcs/docker-compose.yml rm -f -v 

fclean: clean
	docker compose -f ./srcs/docker-compose.yml down -v
	docker compose -f ./srcs/docker-compose.yml down --rmi all
	sudo rm -rf /home/dabouab/data

.PHONY: clean fclean stop all
