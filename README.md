# Simulation of Real-World Process

<h3>Užduoties sąlyga:</h3>
<p>Banko skolų dengimas (ADT: eilė, prioritetinė eilė). Bankas išduoda klientui paskolą, pagal jos sumą ir paskolos laikotarpį sudaromas grąžinimo grafikas (paskolinta suma grąžinama lygiomis dalimis kas 30 dienų). Deja, ne visi klientai sugeba grąžinti paskolą laiku. Atėjus mokėjimo dienai klientas gali turėti tik tiek pinigų, kiek reikia einamajai įmokai pagal grafiką dengti, arba kažkiek daugiau pinigų (tokiu atveju jis dengia ir įsiskolinimus, jei tokių yra), arba kažkiek mažiau pinigų (tokiu atveju auga skolos). Palūkanos skaičiuojamos už visą tam momentui negrąžintą paskolos sumą. Už laiku negrąžintą paskolos dalį imami delspinigiai (delspinigiai neskaičiuojami nuo palūkanų ir delspinigių). Galimos 2 skolų dengimo strategijos: 1) dengiamos seniausios skolos, neatsižvelgiant į jų tipą; 2) dengiama pagal prioritetus: pagrindinė suma, palūkanos, delspinigiai. Įvertinti šių strategijų  ekonominį poveikį klientui. Visi kiti rodikliai, nuo kurių priklauso procesas, įvedami kaip programos parametrai.</p>

<h3>Trumpai apie programą:</h3>
<ul>
<li>Bank.c yra main failas, o Customer.h yra laikomos visos realizuotos funkcijos. Queue.h yra mano realizuotas ADT, o PriorityQueue.h - grupės draugo. Programai papildomai yra padarytas Makefile.</li>
<li>Iš pradžių įvedami pradiniai duomenys - paskolos suma, laikotarpis mėnesiais, palūkanų ir delspinigių procentai. Visi šie parametrai saugomi Customer struktūroje.</li>
<li>Sukuriamas ir išvedamas paskolos grąžinimo grafikas pagal anuitetą, jog grąžinama suma būtų vienoda. Čia pat kiekvieno mėnesio paskolos dalis ir palūkanos įdedamos į eilę, nes jų mums reikės antroje strategijoje. Kadangi kiekvieną mėnesį įmoka yra vienoda, ją laikome kaip kintamąjį. Visi šie duomenys vėl saugomi Customer struktūroje.</li>
<li>Gauame vartotojo mėnesinę sumą. Šią sumą lyginame su įmokos suma:
  <ol>
		<li type = "1">jei šios sumos sutampa.... realiai programoje taip niekad neįvyks. Skaičiai yra su kableliu, o apvalinti pavyksta juos tik vizualiai. Net jei ir bandysime apvalinti dalindami, šis skaičius realiai niekada nebus tikslus (žr. programos pavyzdį apačioje). Dėl šios priežasties paskolos grąžinimo grafike pasirinkau nurodyti tris skaičius po kablelio.</li>
		<li type = "1">jei vartotojo nurodyta suma yra mažesnė už įmokos sumą - išvedame atitinkamą pranešimą. Tuomet pagal pirmą strategiją į debtQueue eilę įdedama visa įmokos suma + paskaičiuoti delspipnigiai, o pagal antrą strategiją į debtPQueue įdedamos trys reikšmės pagal prioritetą - paskolos dalis, palūkanos ir delspinigiai.</li>
		<li type = "1">jei nurodyta suma yra didesnė už įmokos sumą - pirmiausiai sumokame mėnesinę įmoka. Vėliau paskaičiuojame pinigų likutį. Jei šis likutis gali padengti skolą pagal pirmą strategiją arba pagal antrą strategiją, išvedame pranešimą apie sėkmingai sumokėtą skolą ir šią skolą išemame atitinkamai iš eilės ar prioritetinės eilės</li>
    </li>
</ol>
<li>Pabaigoje įvertiname „šių strategijų ekonominį poveikį klientui“ - suskaičiuojame pirmos ir antros strategijos skolų sumas bei jas palyginame. Strategija geresnė klientui yra ta, kurios skolų suma yra mažesnė.</li>
</ul>
