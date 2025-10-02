FROM docker.elastic.co/logstash/logstash:9.0.1

# Copier les fichiers pipeline
COPY pipeline/ /usr/share/logstash/pipeline/

# Copier la config logstash
COPY config/logstash.yml /usr/share/logstash/config/logstash.yml
