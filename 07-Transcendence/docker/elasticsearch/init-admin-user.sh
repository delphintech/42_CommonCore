#!/bin/bash
set -e

# Lancer Elasticsearch en arrière-plan
/usr/local/bin/docker-entrypoint.sh &

# Attendre qu'Elasticsearch soit prêt
until curl -s -u elastic:${ELASTIC_PASSWORD} http://localhost:9200/_security/_authenticate; do
  echo "Waiting for Elasticsearch to be ready..."
  sleep 5
done

# Créer l'utilisateur admin
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_security/user/kibana_admin" \
  -H "Content-Type: application/json" \
  -d '{
    "password": "testcoucou123",
    "roles": ["kibana_admin"],
    "full_name": "Kibana Admin"
  }'

# Mettre à jour le mot de passe de l'utilisateur système utilisé par Kibana
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_security/user/kibana_system/_password" \
  -H "Content-Type: application/json" \
  -d "{\"password\": \"${KIBANA_SYSTEM_PASSWORD}\"}"

# Créer un rôle personnalisé pour accès aux dashboards (sur index app-logs-write)
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_security/role/dashboard_user" \
  -H "Content-Type: application/json" \
  -d '{
    "cluster": ["monitor"],
    "indices": [
      {
        "names": ["app-logs-write"],
        "privileges": ["read", "view_index_metadata"]
      }
    ],
    "applications": [
      {
        "application": "kibana-.kibana",
        "privileges": ["read"],
        "resources": ["*"]
      }
    ]
  }'

# Créer ou mettre à jour l'utilisateur "marie"
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_security/user/${KIBANA_USER}" \
  -H "Content-Type: application/json" \
  -d "{
    \"password\": \"${KIBANA_PASS}\",
    \"roles\": [\"kibana_admin\", \"dashboard_user\"],
    \"full_name\": \"Marie Admin\"
  }"


# Ajouter la policy ILM
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_ilm/policy/log-retention-policy" -H "Content-Type: application/json" -d '
{
  "policy": {
    "phases": {
      "hot": {
        "actions": {
          "rollover": {
            "max_age": "7d",
            "max_size": "1gb"
          }
        }
      },
      "delete": {
        "min_age": "10d",
        "actions": {
          "delete": {}
        }
      }
    }
  }
}'

# Créer le template d'index lié à ILM
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_index_template/app-logs-template" -H "Content-Type: application/json" -d '
{
  "index_patterns": ["app-logs-*"],
  "template": {
    "settings": {
      "index.lifecycle.name": "log-retention-policy",
      "index.lifecycle.rollover_alias": "app-logs-write",
      "number_of_shards": 1
    }
  }
}'

# Créer le premier index avec alias pour le rollover
curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/app-logs-000001" -H "Content-Type: application/json" -d '
{
  "aliases": {
    "app-logs-write": {
      "is_write_index": true
    }
  }
}'

curl -u elastic:${ELASTIC_PASSWORD} -X PUT "http://localhost:9200/_cluster/settings" \
-H "Content-Type: application/json" \
-d '{
  "transient": {
    "indices.lifecycle.poll_interval": "1m"
  }
}'

# Garder Elasticsearch actif
wait
