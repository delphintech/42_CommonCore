# Transcendance

## Launch with `make`

## Add node modules
```
make terminal
node
npm install <module_name>
```


## Compile tailwind
```
make term
node
npm run tailwind
```


## Reset database and seed
```
make term
node
npm run seed
```


## Front
> mettre 'data-link' sur les liens

> considerer la direction 'assets' comme la root (pour appeler l'image */assets/image.jpg*, il faut seulement appeler *image.jpg*)


## Useful installed packages
> Plenty of useful fonctions
> **[Underscore](https://underscorejs.org/)**


## Get current user inf functions 
```
req.user
```

## To check data delition

curl -u elastic:${ELASTIC_PASSWORD} -X GET "http://localhost:9200/app-logs-*/_ilm/explain?pretty"
curl -u elastic:${ELASTIC_PASSWORD} -X GET "http://localhost:9200/_cat/indices/app-logs-*?v"
