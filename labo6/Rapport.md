# Laboratoire 06 PCO

> - Jérôme Arn 
>- Tiffany Bonzon

## Étape 1

Afin de réaliser cette étape, nous avons décider de séparer les fles d'attentes par le type de calcul demandé (A, B, ou C). 

Chacune de ces files acceptent jusqu'au nombre de calculs passé au constructeur, par exemple avec `ComputationManager(8)`, chaque file pourra avoir 8 calculs avant que les calculs suivants soient mis en attente. Une fois qu'un calcul est ajouté à une des files, on envoie un signal particulier à la file pour indiquer aux threads attendant qu'elle ne soit plus vide qu'elle ne l'est plus (je...sais pas comment j'ai eu 5.6 en COMM)

Les threads voulant récupérer un calcul attendent que leur file ne soit plus vide. Une fois un calcul récupérer par le thread, le calcul sera supprimé de la file d'attente.

### Test

Nous avons commencé par vérifier que les tests automatisés passaient 

![](./images/tests1.png)

Puis nous avons tester avec la GUI fournie que les calcule étaient bien placés dans la file demandée, et également que la taille des files n'était pas dépassée

![](./images/etape1File.png)

- Nous voyons ici que les calculs sont ajoutés à la file séléctionnée

- Nous voyons également que le dernier calcul de la file A est en attente, car la file est pleine

## Étape 2 

### Test

## Étape 3 

### Test

## Étape 4 

### Test