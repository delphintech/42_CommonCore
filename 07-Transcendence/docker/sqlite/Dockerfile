FROM	alpine:3.20

RUN     apk update && apk upgrade && apk add sqlite sqlite-libs sqlite-dev

WORKDIR	/db

EXPOSE	1433

RUN		if [ ! -f "/db/transc.sqlite" ]; then sqlite3 "/db/transc.sqlite";	fi

CMD ["sh", "-c", "tail -f /dev/null"]

