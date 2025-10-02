#!/bin/sh
set -e

echo "Generating alertmanager.yml from template..."

sed \
  -e "s|\${AM_SMTP_USER}|${AM_SMTP_USER}|g" \
  -e "s|\${AM_SMTP_PASSWORD}|${AM_SMTP_PASSWORD}|g" \
  -e "s|\${AM_DEST}|${AM_DEST}|g" \
  -e "s|\${AM_SMTP_HOST}|${AM_SMTP_HOST}|g" \
  /etc/alertmanager/alertmanager.yml.template > /etc/alertmanager/alertmanager.yml

echo "Starting Alertmanager..."
exec /bin/alertmanager --config.file=/etc/alertmanager/alertmanager.yml --web.external-url=http://localhost:8081 "$@"
