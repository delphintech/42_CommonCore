# pull the base image
FROM nginx:stable-alpine

# install the required packages (apk = le gestionnaire de paquets Alpine) no cache pour eviter les fichiers inutiles
RUN apk add --no-cache openssl

RUN openssl version

# create the certs directory in the container to store the certificates
RUN mkdir -p /etc/nginx/certs

# generate the ssl certificate
# keyout private key
# out public key
# subj for id data
RUN openssl req -x509 -nodes \
    -out /etc/nginx/certs/transcendance.crt \
    -keyout /etc/nginx/certs/transcendance.key \
    -subj "/C=FR/ST=IDF/L=PARIS/O=42/OU=75/CN=localhost"


# copy the nginx configuration file
COPY ./nginx.conf /etc/nginx/nginx.conf
