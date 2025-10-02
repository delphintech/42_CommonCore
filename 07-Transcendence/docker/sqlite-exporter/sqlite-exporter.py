from flask import Flask, Response
import sqlite3
from prometheus_client import Gauge, generate_latest, CONTENT_TYPE_LATEST

app = Flask(__name__)
DB_PATH = "/data/transc.sqlite"

# Déclaration des métriques Prometheus
user_count_gauge = Gauge('sqlite_users_count', 'Nombre de lignes dans la table users')
game_count_gauge = Gauge('sqlite_games_count', 'Nombre de lignes dans la table games')
tournament_count_gauge = Gauge('sqlite_tournaments_count', 'Nombre de lignes dans la table tournaments')

def query_count(table):
    try:
        conn = sqlite3.connect(DB_PATH)
        cursor = conn.cursor()
        cursor.execute(f"SELECT COUNT(*) FROM {table}")
        count = cursor.fetchone()[0]
        conn.close()
        return count
    except Exception as e:
        print(f"Erreur SQLite pour table '{table}': {e}")
        return None

@app.route('/metrics')
def metrics():
    user_count = query_count('users')
    game_count = query_count('games')
    tournament_count = query_count('tournaments')

    user_count_gauge.set(user_count or 0)
    game_count_gauge.set(game_count or 0)
    tournament_count_gauge.set(tournament_count or 0)

    return Response(generate_latest(), mimetype=CONTENT_TYPE_LATEST)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=9560)
