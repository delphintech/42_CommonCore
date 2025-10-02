#!/bin/sh
set -e

# Attendre que Kibana soit prêt via l'API status
until curl -sk "$KIBANA_URL/api/status" | jq -e '.status.overall.level == "available"' > /dev/null; do
  echo "Waiting for Kibana via Nginx...";
  sleep 5;
done

# Importer le dashboard
curl -k -u "$KIBANA_USER:$KIBANA_PASS" \
  -X POST "$KIBANA_URL/api/saved_objects/_import?overwrite=true" \
  -H "kbn-xsrf: true" \
  -F file=@/dashboard.ndjson
