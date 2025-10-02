FROM docker.elastic.co/elasticsearch/elasticsearch:9.0.1

USER root

COPY init-admin-user.sh /usr/local/bin/init-admin-user.sh
RUN chmod +x /usr/local/bin/init-admin-user.sh

USER elasticsearch

ENTRYPOINT ["/usr/local/bin/init-admin-user.sh"]
