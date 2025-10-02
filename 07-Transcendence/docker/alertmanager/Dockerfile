FROM prom/alertmanager:latest

USER root

COPY alertmanager.yml.template /etc/alertmanager/alertmanager.yml.template
COPY entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

USER nobody

ENTRYPOINT ["/entrypoint.sh"]
