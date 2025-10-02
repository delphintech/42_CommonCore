all:
	mkdir -p data
	mkdir -p logs/nginx
	docker compose -f ./docker/docker-compose.yml up -d

stop:
	docker compose -f ./docker/docker-compose.yml down

term:
	@echo "Container name ?"; \
	read CONT; \
	docker exec -it $$CONT sh

clean:
	docker compose -f ./docker/docker-compose.yml rm -f -v

fclean: clean
	docker compose -f ./docker/docker-compose.yml down -v
	docker compose -f ./docker/docker-compose.yml down --rmi all
	rm -rf data
	rm -rf app/dist
	rm -rf logs

prune:
	docker system prune -a

.PHONY: clean fclean stop all prune
