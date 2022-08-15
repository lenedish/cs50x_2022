-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street

-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape

SELECT description
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- bakery - пекарня

------------------------------------------------

SELECT name, transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28

-- Three interviews

-- (Ruth) Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- (Eugene) I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- (Raymond) As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest
-- flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone
-- to purchase the flight ticket.

-- Выводы:
-- 1. (Ruth) Парковка.Вор уехал с места приступления через десять минут после кражи. Записи с камер на парковке

-- 2. Юджин не знает имя вора, но это тот кого он узнал. Когда он проходил по улице Leggett Street, он увидел
-- как вор снимает деньги с банкомата

-- 3. (Raymond) Когда вор покидал пикарню он позвонил кому-то с кем говорил меньше минуты. Раймонд услышал
-- как вор говорил о покупке билета на самолет из Fiftyville на завтра. В конце разговора вор попросил
-- сообщника купить билет на самолет

------------------------------------------------

-- Логи с места парковки в течении 10 минут после кражи
SELECT activity, license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25

------------------------------------------------

-- Поиск людей по номерному знаку их авто
SELECT name
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25)

-- Люди кто уезжал с парковки в течении 10 минут после кражи:
-- Vanessa, Barry, Iman, Sofia, Luca, Kelsey, Bruce (8 человек)

-- Поиск остальной информации. Номер телефона, номер паспорта
SELECT name, phone_number, passport_number
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25)

------------------------------------------------

-- Поиск id полета и код места в самолете, через номер паспорта
SELECT flight_id, seat
FROM passengers
WHERE passport_number IN
    (SELECT passport_number
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25))

------------------------------------------------
-- Поиск в таблице flight по flight_id из passengers. Где день 29 (следующий день после кражи) и где время меньше 10
SELECT origin_airport_id
FROM flights
WHERE id IN
    (SELECT flight_id
    FROM passengers
    WHERE passport_number IN
        (SELECT passport_number
        FROM people
        WHERE license_plate IN
            (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25)))
AND day = 29
AND hour < 10

-- Поиск origin airport
SELECT id, abbreviation, full_name, city
FROM airports
WHERE id IN
(SELECT origin_airport_id
FROM flights
WHERE id IN
    (SELECT flight_id
    FROM passengers
    WHERE passport_number IN
        (SELECT passport_number
        FROM people
        WHERE license_plate IN
            (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25)))
AND day = 29
AND hour < 10)

-- Origin airport. 8, CSF, Fiftyville Regional Airport, Fiftyville

-- Поиск destination airport
SELECT id, abbreviation, full_name, city
FROM airports
WHERE id IN
(SELECT destination_airport_id
FROM flights
WHERE id IN
    (SELECT flight_id
    FROM passengers
    WHERE passport_number IN
        (SELECT passport_number
        FROM people
        WHERE license_plate IN
            (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25)))
AND day = 29
AND hour < 10)

-- Destination airport. 4, LGA, LaGuardia Airport, New York City

-- Вывод: вор улетел в New York City

------------------------------------------------

-- Попытка найти вора. Нужен номер телефона
SELECT people.name, passengers.passport_number, people.phone_number
FROM passengers JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.passport_number IN
    (SELECT passport_number
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25))
AND flights.day = 29

------------------------------------------------
-- Поиск номеров аккакунтов по дате и улице где находился банкомат
SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street"

------------------------------------------------
-- Поиск person id и creation year через номер аккаунта
SELECT person_id, creation_year
FROM bank_accounts
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = "Leggett Street")

------------------------------------------------

-- Люди который делали транзакцию на Leggett Street
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))

------------------------------------------------

-- Пересечение людей которые уезжали со стоянки и делали транзакцию
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))
INTERSECT
SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25)

-- Осталось 4 подозреваемых: Bruce, Diana, Iman, Luca

-- Пересечение людей которые уезжали со стоянки и делали транзакцию, а также были на рейсе 29 числа
SELECT people.name
FROM passengers JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.passport_number IN
    (SELECT passport_number
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25))
AND flights.day = 29
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))

-- Осталось 3 подозреваемых: Bruce, Diana, Luca

------------------------------------------------

-- Поиск номеров по дате звонка и длительности (меньше минуты)
SELECT caller
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration <= 60

------------------------------------------------
-- Пересечение людей которые уезжали со стоянки и делали транзакцию, были на рейсе 29 числа, а также делали звонок длительностью меньше минуты

SELECT people.name
FROM passengers JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE passengers.passport_number IN
    (SELECT passport_number
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25))
AND flights.day = 29
AND people.phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60)
INTERSECT
SELECT name
FROM people
WHERE id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = "Leggett Street"))

-- Осталось 2 подозреваемых: Bruce, Diana

------------------------------------------------
-- Номера получателей
SELECT receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration <= 60

-- Номера Дианы и Брюса
SELECT name, phone_number
FROM people
WHERE name IN
    (SELECT people.name
    FROM passengers JOIN people ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    WHERE passengers.passport_number IN
        (SELECT passport_number
        FROM people
        WHERE license_plate IN
            (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 25))
    AND flights.day = 29
    AND people.phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60)
    INTERSECT
    SELECT name
    FROM people
    WHERE id IN
        (SELECT person_id
        FROM bank_accounts
        WHERE account_number IN
            (SELECT account_number
            FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street")))

-- Этап 1
SELECT receiver
FROM phone_calls
WHERE caller IN
	(SELECT phone_number
	FROM people
	WHERE name IN
		(SELECT people.name
		FROM passengers JOIN people ON passengers.passport_number = people.passport_number
		JOIN flights ON flights.id = passengers.flight_id
		WHERE passengers.passport_number IN
			(SELECT passport_number
			FROM people
			WHERE license_plate IN
				(SELECT license_plate
				FROM bakery_security_logs
				WHERE year = 2021
				AND month = 7
				AND day = 28
				AND hour = 10
				AND minute BETWEEN 15 AND 25))
		AND flights.day = 29
		AND people.phone_number IN
		(SELECT caller
		FROM phone_calls
		WHERE year = 2021
		AND month = 7
		AND day = 28
		AND duration < 60)
		INTERSECT
		SELECT name
		FROM people
		WHERE id IN
			(SELECT person_id
			FROM bank_accounts
			WHERE account_number IN
				(SELECT account_number
				FROM atm_transactions
				WHERE year = 2021
				AND month = 7
				AND day = 28
				AND atm_location = "Leggett Street"))))
AND month = 7
AND day = 28
AND duration <= 60


-- Этап 2
SELECT name
FROM people
WHERE phone_number IN
	(SELECT receiver
	FROM phone_calls
	WHERE caller IN
		(SELECT phone_number
		FROM people
		WHERE name IN
			(SELECT people.name
			FROM passengers JOIN people ON passengers.passport_number = people.passport_number
			JOIN flights ON flights.id = passengers.flight_id
			WHERE passengers.passport_number IN
				(SELECT passport_number
				FROM people
				WHERE license_plate IN
					(SELECT license_plate
					FROM bakery_security_logs
					WHERE year = 2021
					AND month = 7
					AND day = 28
					AND hour = 10
					AND minute BETWEEN 15 AND 25))
			AND flights.day = 29
			AND people.phone_number IN
			(SELECT caller
			FROM phone_calls
			WHERE year = 2021
			AND month = 7
			AND day = 28
			AND duration < 60)
			INTERSECT
			SELECT name
			FROM people
			WHERE id IN
				(SELECT person_id
				FROM bank_accounts
				WHERE account_number IN
					(SELECT account_number
					FROM atm_transactions
					WHERE year = 2021
					AND month = 7
					AND day = 28
					AND atm_location = "Leggett Street"))))
	AND month = 7
	AND day = 28
	AND duration <= 60)

-- Philip и Robin. Имена людей которым звонили Диана и Брюс, которые были 28 числа и длилилсь меньше минуты
-- В итоге вор либо Диана либо Брюс и сообщник либо Филип либо Робин

------------------------------------------------

-- Попытка выяснить кто кому звонил
SELECT id
FROM phone_calls
WHERE caller = "(770) 555-1861"
AND receiver = "(725) 555-3243"

-- id = 255

SELECT caller, receiver
FROM phone_calls
WHERE id = 255

SELECT name
FROM people
WHERE phone_number IN
(SELECT caller
FROM phone_calls
WHERE id = 255)
-- Caller Diana

SELECT name
FROM people
WHERE phone_number IN
(SELECT receiver
FROM phone_calls
WHERE id = 255)
-- Receiver Philip

-- Диана и Филип звонили друг другу. Если не они вор и сообщник, тогда это Брюс и Робин
-- Методом перебора выясниснилось что это Брюс и Робин
-- Брюс - это вор, а Робин - сообщник














