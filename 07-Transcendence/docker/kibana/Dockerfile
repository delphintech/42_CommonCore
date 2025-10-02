FROM docker.elastic.co/kibana/kibana:9.0.0

USER root

COPY kibana.yml /usr/share/kibana/config/kibana.yml
COPY dashboards/dashboard.ndjson /kibana/dashboards/dashboard.ndjson

USER kibana
