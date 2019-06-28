 /--1--
--1.1
create table Mitarbeiter 
( MitID char(3) PRIMARY KEY NOT NULL,
  MitName varchar(20) NOT NULL,
  MitVorname varchar(20) NULL,
  MitGebDat date NOT NULL,
  MitJob varchar(20) NOT NULL,
  MitStundensatz smallmoney NULL,
  MitEinsatzort varchar(20) NULL  
)

create table Kunde 
( KunNr int PRIMARY KEY NOT NULL,
  KunName varchar(20) NOT NULL,
  KunOrt varchar(20) NOt NULL,
  KunPLZ char(5) NOT NULL,
  KunStrasse varchar(20) NOT NULL
)

create table Ersatzteil 
( EtID char(5) PRIMARY KEY NOT NULL,
  EtBezeichnung varchar(100) NOT NULL,
  EtPreis smallmoney NOt NULL,
  EtAnzLager int NOT NULL,
  EtHersteller varchar(30) NOT NULL
)

SELECT * FROM Mitarbeiter;
SELECT * FROM Kunde;
SELECT * FROM Ersatzteil;

--1.2
INSERT INTO Mitarbeiter SELECT * FROM trommelhelden..quelleMitarbeiter;
INSERT INTO Kunde SELECT * FROM trommelhelden..quelleKunde;
INSERT INTO Ersatzteil SELECT * FROM trommelhelden..quelleErsatzteiL;
--1.3
SELECT * INTO Auftrag FROM trommelhelden..quelleAuftrag;
SELECT * INTO Montage FROM trommelhelden..quelleMontage;
--1.4
ALTER TABLE Auftrag 
    ADD CONSTRAINT pk_AufNr PRIMARY KEY(AufNr)

ALTER TABLE Auftrag 
	ADD CONSTRAINT fk_MitID FOREIGN KEY(MitID)
	    REFERENCES Mitarbeiter(MitID)

ALTER TABLE Auftrag 
	ADD CONSTRAINT fk_KunNr FOREIGN KEY(KunNr)
	    REFERENCES Kunde(KunNr)

ALTER TABLE Montage
    ADD PRIMARY KEY(EtID, AufNr)

ALTER TABLE Montage
	ADD CONSTRAINT fk_EtID FOREIGN KEY(EtID)
		REFERENCES Ersatzteil

ALTER TABLE Montage
	ADD CONSTRAINT fk_AufNr FOREIGN KEY(AufNr)
		REFERENCES Auftrag

--1.6
SELECT COUNT(*) AS Auftrag FROM Auftrag 
SELECT COUNT(*) AS Ersatzteil FROM Ersatzteil
SELECT COUNT(*) AS Kunde FROM Kunde
SELECT COUNT(*) AS Mitarbeiter FROM Mitarbeiter
SELECT COUNT(*) AS Montage FROM Montage

-- 1.8
create unique index MitNameVorname on Mitarbeiter(Mitname, Mitvorname);
-- für löschen
-- drop index MitNameVorname on Mitarbeiter

-- 2 --
-- 2.1
  -- a
SELECT COUNT(*) FROM Mitarbeiter 
WHERE MitEinsatzort='Dresden'
  -- b
SELECT COUNT(*) FROM Kunde 
WHERE KunOrt not like 'Leipzig'
  -- c
SELECT * FROM Ersatzteil 
WHERE EtBezeichnung like 'E%'
  -- d
SELECT MitName, MitJob  FROM Mitarbeiter
WHERE MitEinsatzort='Chemnitz' AND MitJob in ('Azubi','Monteur')
ORDER BY MitName
  -- e
SELECT * FROM Auftrag 
WHERE Dauer>3 OR Anfahrt>80
  -- f
SELECT * FROM Auftrag 
WHERE Dauer IS NULL
  -- g
SELECT AufNr, Anfahrt, Anfahrt*2.5 AS AnfahrtKosten FROM Auftrag
WHERE Dauer IS NOT NULL
  -- h
SELECT MitStundensatz FROM Mitarbeiter 
WHERE MitJob like 'Meister'
  -- i
select EtPreis*EtAnzLager as LagerWert from Ersatzteil

-- 2.2
  -- a
  SELECT COUNT(*) FROM Kunde
  -- b 
  SELECT KunOrt,COUNT(*) FROM Kunde
  GROUP BY KunOrt
  -- c
  SELECT MitID, AVG(Dauer) as 'Auftragsbearbeitungszeit' FROM Auftrag
  WHERE MitID is NOT NULL
  GROUP BY MitID
  
  SELECT MitID, ErlDat, AVG(Dauer) as 'Auftragsbearbeitungszeit', count(Aufnr) as 'pro Tag' FROM Auftrag
  WHERE MitID is NOT NULL AND Dauer is NOT NULL
  GROUP BY MitID,ErlDat
  -- d
  SELECT max(EtPreis*EtAnzLager) as LBW_max, min(EtPreis*EtAnzLager) as LBW_min,
  sum(EtPreis*EtAnzLager) as LBW_sum from Ersatzteil
-- 2.3
  -- a
  SELECT MitName, MitVorname, MitGebDat, DATEDIFF(yy,MitGebDat,GETDATE()) AS Alter_jj FROM Mitarbeiter
  -- b
  SELECT * from Auftrag
  where DATEDIFF(dd, AufDat, ErlDat)>4 AND Dauer IS NOT null
  -- c
  SELECT * from Auftrag
  where Month(AufDat) = 4
  -- d 
  SELECT * from Auftrag
  where Month(GETDATE()) = Month(AufDat)
    AND Year(GETDATE()) = Year(AufDat)
  order BY AufDat
  -- e
  SELECT avg(DATEDIFF(dd, AufDat, ErlDat)) FROM Auftrag
  -- f
  SELECT Month(AufDat) as Monat,avg(DATEDIFF(dd, AufDat, ErlDat)) as Durchschnitt FROM Auftrag
  Group by Month(AufDat)
  Order by Monat
  -- g
  Select MitJob, avg(datediff(year, MitGebDat,getdate())) as durchschnittliches_alter_beim_job
  from Mitarbeiter group by Mitjob
  -- 2.4
  -- a
    -- aufgabe
  SELECT AufNr, EtBezeichnung, Anzahl, EtPreis, Anzahl*EtPreis as Lagerbestandwert 
  from Montage m, Ersatzteil e 
  where m.EtID = e.EtID
  order by Aufnr
    -- lösung
  SELECT AufNr, EtBezeichnung, Anzahl, EtPreis, Anzahl*EtPreis as Lagerbestandwert 
  from Montage m 
  join Ersatzteil e 
  on m.EtID = e.EtID
  order by Aufnr
  -- b 
  SELECT AufNr, Dauer*MitStundensatz as kosten
  from Auftrag a
  join Mitarbeiter m
  on a.MitID = m.MitID
  where Dauer is not null
  -- c
  SELECT KunName, KunOrt, Anfahrt as Anfahrtsweg 
  from Kunde k 
  join Auftrag a ON k.KunNr = a.KunNr
  where Anfahrt > 50
  -- d 
  SELECT KunName, k.KunNr
  from Montage m 
  join Auftrag a
  on m.AufNr = a.AufNr
  join Kunde k
  on a.KunNr = k.KunNr
  where m.EtID = 'P0110' 
  --e
  -- ?? muss es nicht sum sein 
  SELECT 
    a.AufNr, 
    sum(e.EtPreis*m.Anzahl) 
      AS Materialkosten, 
    avg(a.Dauer*f.MitStundensatz) 
      AS Lohnkosten,
    avg(Anfahrt*2.5) 
      AS AnfahrtKosten  
  FROM Auftrag a
  JOIN Montage m 
  ON a.AufNr = m.AufNr
  JOIN Ersatzteil e
  ON m.EtID = e.EtID
  JOIN Mitarbeiter f 
  ON f.MitID = a.MitID
  WHERE Dauer IS NOT NULL
  GROUP BY a.AufNr
  ORDER BY a.AufNr  
  --f
  SELECT AufNr, MitName
  FROM Auftrag auf
  LEFT JOIN Mitarbeiter m
  ON auf.MitID = m.MitID
  WHERE month(auf.AufDat) = month(getdate())  
-- 2.5
  -- a
  SELECT * FROM Mitarbeiter
  WHERE MitID NOT IN (
    select MitID from Auftrag 
    where month(AufDat) = month(getdate())
        and year(AufDat) = year(getdate())
        and MitID is not NULL
  )
  -- b
  SELECT AufNr, a.Dauer*f.MitStundensatz AS Lohnkosten, Anfahrt*2.5 AS AnfahrtKosten from Auftrag a
  JOIN Mitarbeiter f 
  ON f.MitID = a.MitID
  WHERE AufNr not in ( SELECT AufNr 
    From Montage) and Dauer is not null
  order by AufNr
  -- c
  SELECT * from Mitarbeiter
  Where DATEDIFF(yy,MitGebDat,getdate()) <= ALL(
    SELECT DATEDIFF(yy,MitGebDat,getdate()) from Mitarbeiter
    where  MitJob like 'Monteur'
  )
  and MitJob like 'Monteur'
  -- d
   -- 1   
   SELECT AufNr,MitID from Auftrag a
   where Dauer = (
     SELECT max(Dauer) from Auftrag a1
     where a.MitID = a1.MitID
   )
   order by AufNr
   -- 2
   SELECT * from (
     SELECT MitID, max(Dauer) as mzeit from Auftrag
     where dauer is not null and MitID is not null
     group by MitID
   ) UA
   join Auftrag a ON a.MitID = UA.MitID
                  and UA.mzeit = a.Dauer                                                                                                                                                                                                  
-- 2.6
  -- a
  SELECT MitID, sum(a.Anfahrt) FROM Auftrag a
    WHERE month(a.AufDat) = 4
  GROUP BY MitID
    HAVING sum(a.Anfahrt) > 1500
  -- b
    SELECT e.EtID, e.EtBezeichnung, EtAnzLager as Lager, sum(Anzahl) as Verbaut 
    FROM Ersatzteil e
    join Montage m 
    on e.EtID = m.EtID
    group by e.EtID, e.EtBezeichnung, e.EtAnzLager
    having EtAnzLager > sum(Anzahl)
-- 2.7
  -- a
  INSERT INTO Kunde VALUES(1, 'Lucas Opitz', 'Eibenstock', 08309, 'Huher weg')
  INSERT INTO Auftrag VALUES(1771, 103, 1, getdate(), null, null, 144, 'geplatze Abflußleitung')
  -- b 
  UPDATE Mitarbeiter set MitName = 'Nass'
  where MitName like 'Igel'
  !! geht nicht wegen Indizes
  -- c
  UPDATE Mitarbeiter
  set MitStundensatz = (
    Select min(MitStundensatz) from Mitarbeiter
    where MitJob like 'Monteur'
  ),
      MitJob = 'Monteur'
  where MitJob like 'Azubi'
  -- d
  -- zuerst from Montage
    delete from Montage
    where EtID in (
        select EtID
        from  Ersatzteil
        where EtHersteller like 'Hauknecht'
    )
   -- dann die ET selbst
    delete from Ersatzteil
    where EtHersteller like 'Hauknecht'
  -- e
    create table AufNrToDelete
    (
        EtID  char(5) PRIMARY KEY NOT NULL
    )
  
    -- insert die zu löschen sind
    insert into AufNrToDelete
    select EtID from Montage 
    where AufNr in 
    (
     Select AufNr from Auftrag
        where month(AufDat) = 3
        and KunNr not in (
        select KunNr from Auftrag 
        where month(AufDat) <> 3
        )
    )
    group by EtID   
  
  -- Montage löschen
    delete from Montage 
    where AufNr in 
    (
     Select AufNr from Auftrag
        where month(AufDat) = 3
        and KunNr not in (
        select KunNr from Auftrag 
        where month(AufDat) <> 3
        )
    )
    
    delete from Montage
    where Aufnr in (
        select Aufnr from Auftrag 
        where month(AufDat)=3
    )
  --  Ersatzteile aus Hilfstabelle
    select * from Ersatzteil 
    where EtID in 
    (
       select EtID from AufNrToDelete
    ) 
    and EtID not in (
       select EtId  from Montage 
    )
  -- KUNR SPREICHERN
    create table hilfsTable
    (
        Kunnr char(5) PRIMARY KEY NOT NULL
    )
    insert into hilfsTable
    select KunNr from Kunde 
    where KunNr in (
        Select KunNr from Auftrag
        where month(AufDat) = 3
        and KunNr not in (
        select KunNr from Auftrag 
        where month(AufDat) <> 3
        )
    )
 -- auftrage zu loschen
    select * from Auftrag 
    where AufNr in (
        Select AufNr from Auftrag
        where month(AufDat) = 3
        and KunNr not in (
          select KunNr from Auftrag 
          where month(AufDat) <> 3
        )
    )
  --- kunde zu loschen
    delete from Kunde
    where KunNr in
    (
        select kunnr from hilfsTable
    )
    
-- 2.8
Select kunort from Kunde
except
Select miteinsatzort from Mitarbeiter

Select kunort from Kunde
intersect
Select miteinsatzort from Mitarbeiter

Select kunort from Kunde
union
Select miteinsatzort from Mitarbeiter
-- 2.9
-- a
Select * from Kunde, Mitarbeiter
-- b
Select * from Kunde k
join Mitarbeiter m 
on k.kunort=m.miteinsatzort 
-- c
Select m.*, kunort from Kunde k
join Mitarbeiter m 
on k.kunort=m.miteinsatzort

-- 2.10
-- create view
Create view Auftragswert 
as 
select 
    a.AufNr,
    a.ErlDat,
    k.KunOrt,
    sum(e.EtPreis*m.Anzahl) AS Materialkosten, 
    avg(Anfahrt*2.5) AS AnfahrtKosten,
    avg(a.Dauer*f.MitStundensatz) AS Lohnkosten
FROM Auftrag a

  JOIN Montage m 
  ON a.AufNr = m.AufNr
  JOIN Ersatzteil e
  ON m.EtID = e.EtID
  JOIN Mitarbeiter f 
  ON f.MitID = a.MitID
  JOIN Kunde k
  ON a.KunNr = k.Kunnr
  WHERE Dauer IS NOT NULL
  GROUP BY a.AufNr, a.ErlDat, k.KunOrt
-- ermitteln Gesamtwert
  select 
    aufnr,
    sum(materialkosten+anfahrtkosten+lohnkosten) as Gesamtwert
  from Auftragswert
  group by aufnr
  
  
-- 2.11
select Anfahrt,
    CASE
      WHEN Anfahrt < 12 THEN  30
      --WHEN  THEN
      ELSE Anfahrt*2.5
    END as Preis
from Auftrag
-- 3
-- 3.1
create procedure dreieins
    as
    select 
        a.MitID, 
        a.Kunnr,
        Count(*) as anzahl

    from Mitarbeiter m
    join Auftrag a 
    on a.MitID = m.MitID
    group by a.MitID, a.Kunnr
    order by a.MitID
-- 3.2
create procedure dreizwei(@MinAngebaut INT)
as 
select EtID,sum(Anzahl) as Anzahl 
from Montage
group by EtID
having sum(Anzahl)> @MinAngebaut
-- 3.3
-- copy von Tabelle erstellen
select * into Auftrag2 from Auftrag
-- return of rest 
  Declare @rest INT
  select @rest = Count(*) 
        from Auftrag2
        where Dauer is null
        and   ErlDat is not null
  print @rest
-- erster tag
select * from Auftrag2
where AufDat in (
    select min(AufDat) from Auftrag2
    where Dauer is null
    and   ErlDat is not null

-- procedure für ändern
create procedure dreidrei(@tagen INT)
as
Declare @i INT
set @i = 0
while (@i < @tagen)
    begin
        update Auftrag2
        set Dauer = (convert(int, rand()*10)*0.5),
         Anfahrt = (convert(int, rand()*100)*5),
         Beschreibung = 'die Werte automatisch ausgefühlt'
        where AufDat in (
            select min(AufDat) from Auftrag2
            where Dauer is null
            and   ErlDat is not null
        ) 
        set @i = @i + 1
    end
Declare @rest INT
select @rest = Count(*) 
    from Auftrag2
    where Dauer is null
    and   ErlDat is not null
print @rest
-- 3.4
create procedure dreivier @tagen INT
as
Declare @i INT
Declare @tmpAufnr INT
set @i = 0
while (@i < @tagen)
    begin
        declare myC cursor
        for
        select Aufnr from Auftrag2 
        where AufDat in (
            select min(AufDat) from Auftrag2
            where Dauer is null
            and   ErlDat is not null
        ) 
        
        open myC
        
        fetch myC
            into @tmpAufnr
            
        if (@@FETCH_STATUS = -2) --Cursor leer?
         begin
          print 'Keine Aufträge gefunden'
          return
         end
        
        while (@@FETCH_STATUS = 0)
         begin
            update Auftrag2
            set Dauer = (convert(int, rand()*10)*0.5),
                Anfahrt = (convert(int, rand()*100)*5),
                Beschreibung = 'die Werte automatisch ausgefühlt'
            where AufNr = @tmpAufnr
            print @tmpAufnr
            fetch myC
                into @tmpAufnr
         end     
        -- cursor löschen
        close myC
        deallocate myC
        
        set @i = @i + 1
        print 'neuer Tag'
    end
-- rest ausgeben
Declare @rest INT
select @rest = Count(*) 
    from Auftrag2
    where Dauer is null
    and   ErlDat is not null
print @rest
