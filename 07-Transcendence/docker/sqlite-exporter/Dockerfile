FROM python:3.11-slim

RUN pip install flask prometheus-client

WORKDIR /app

COPY sqlite-exporter.py /app/sqlite_exporter.py
COPY sqlite-queries.yml /app/sqlite-queries.yml

CMD ["python", "sqlite_exporter.py"]
