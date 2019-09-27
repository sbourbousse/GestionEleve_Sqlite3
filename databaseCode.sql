create table Parametre(
    version float
);

create table Option(
optionId smallint auto_increment primary key,
optionLibelle varchar(64));

create table Etudiant(
etudiantId int primary key,
etudiantPrenom varchar(64),
etudiantNom varchar(64),
optionId smallint,
FOREIGN KEY(optionId) REFERENCES Option(optionId));

insert into Option values (1,"SLAM"),
    (2,"SISR"),
    (3,"SLAM ET SISR");


    --OLD DATABASE--

create table Etudiant(
etudiantId int primary key,
etudiantPrenom varchar(64),
etudiantNom varchar(64),
etudiantOption varchar(64));

create table Parametre(
    version float);

insert into Parametre values (1.2);

insert into Etudiant (etudiantId,etudiantPrenom,etudiantNom,etudiantOption) values 
(1,"sylvain","bourbousse","slam"),
(2,"dorian","paret","SLAM"),
(3,"nicolas","granier","sisr"),
(4,"jeremy","mainard","SiSr"),
(5,"julien","legrand","sisr et slam");


