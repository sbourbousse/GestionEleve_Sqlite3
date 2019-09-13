insert into Option (optionId, optionLibelle)
values (1,'SLAM'),
(2,'SISR'),
(3,'SLAM et SISR');

insert into Etudiant (etudiantId,etudiantNom,etudiantPrenom,optionId) values (1,'Bourbousse','Sylvain',1),
    (2,'Legrand','Julien',3),
    (3,'Paret','Dorian',1);

/* create table Option(
optionId smallint primary key,
optionLibelle varchar(64));

create table Etudiant(
etudiantId int primary key,
etudiantPrenom varchar(64),
etudiantNom varchar(64),
optionId smallint,
FOREIGN KEY(optionId) REFERENCES Option(optionId));*/
