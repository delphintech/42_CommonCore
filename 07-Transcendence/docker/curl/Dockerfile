FROM alpine:latest

RUN apk add --no-cache curl jq

COPY script.sh /script.sh
RUN chmod +x /script.sh

USER nobody

ENTRYPOINT ["/bin/sh", "/script.sh"]

