-- Keep a log of any SQL queries you execute as you solve the mystery.
--lets first find out what is going on
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND street = 'Humphrey Street'
ORDER BY year DESC;
--lets see the interviews
SELECT year, name, transcript FROM interviews
WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';

--transcripts
--| 2021 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car
--in the bakery parking lot and drive away. If you have security footage from the bakery parking
--lot, you might want to look for cars that left the parking lot in that time frame.

SELECT activity, license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25;

+----------+---------------+
| activity | license_plate |
+----------+---------------+
| exit     | 5P2BI95       |
| exit     | 94KL13X       |
| exit     | 6P58WS2       |
| exit     | 4328GD8       |
| exit     | G412CB7       |
| exit     | L93JTIZ       |
| exit     | 322W7JE       |
| exit     | 0NTHK55       |
+----------+---------------+

--| 2021 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this
--morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the
--thief there withdrawing some money.
SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

+----------------+--------+
| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |
+----------------+--------+

--| 2021 | Raymond | As the thief was leaving the bakery, they called someone who talked to them
--for less than a minute. In the call, I heard the thief say that they were planning to take the
--earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of
--the phone to purchase the flight ticket.
SELECT caller, receiver FROM phone_calls
WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 1;
--i cant get the caller and receiver, i might need this to find the accomplace

SELECT id, destination_airport_id, hour, minute FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
ORDER BY hour, minute LIMIT 1;

+----+------------------------+------+--------+
| id | destination_airport_id | hour | minute |
+----+------------------------+------+--------+
| 36 | 4                      | 8    | 20     |
+----+------------------------+------+--------+

SELECT city FROM airports
WHERE id = 4;

--the perp is going to NYC!

SELECT passport_number, seat FROM passengers
WHERE flight_id = 36;

+-----------------+------+
| passport_number | seat |
+-----------------+------+
| 7214083635      | 2A   |
| 1695452385      | 3B   |
| 5773159633      | 4A   |
| 1540955065      | 5C   |
| 8294398571      | 6C   |
| 1988161715      | 6D   |
| 9878712108      | 7A   |
| 8496433585      | 7B   |
+-----------------+------+

--we now need to cross reference the passport number from the flights and the person who used the credit card that morning then use their name to find the call list
SELECT name, phone_number, account_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE passport_number IN(SELECT passport_number FROM passengers
WHERE flight_id = 36) AND license_plate IN(SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25);


+-------+----------------+----------------+
| name  |  phone_number  | account_number |
+-------+----------------+----------------+
| Bruce | (367) 555-5533 | 49610011       |
| Luca  | (389) 555-5198 | 28500762       |
+-------+----------------+----------------+

--took me a while to try inputting in seconds and not minutes xD

SELECT receiver, caller FROM phone_calls
WHERE day = 28 AND month = 7 AND duration < 60
AND caller IN(SELECT phone_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE passport_number IN(SELECT passport_number FROM passengers
WHERE flight_id = 36) AND license_plate IN(SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25));

--our criminals

+----------------+----------------+
|    receiver    |     caller     |
+----------------+----------------+
| (375) 555-8161 | (367) 555-5533 |
+----------------+----------------+

--im too lazy to automate getting the names of the phone numbers
--so im doing it manually

--our accomplace

SELECT name FROM people WHERE phone_number = '(375) 555-8161';

--robin

-------------------
--our robber

SELECT name FROM people WHERE phone_number = '(367) 555-5533';

--bruce

