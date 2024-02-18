-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking the first clues
Select description FROM crime_scene_reports
   ...> Where month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

SELECT transcript FROM interviews WHERE transcript LIKE '%bakery%' AND month = 7 AND day = 28;
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. >>>>>> 10:25
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- CHECK security camera at bakery around 10:25

SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;
                                                         |
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- CHECK ATM at Legget Street that moring
SELECT account_number, amount FROM atm_transactions WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
                                                                                                |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- CHECK phone call
SELECT caller, receiver, duration FROM phone_calls WHERE month = 7 AND day = 28 AND duration =< 60;

-- 2 suspects based on acc number, phone number, license plate
SELECT name FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60)
        AND account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street'
        AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
        AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25);



-- select name based on passport number and city of departure on a specific date >> earliest flight >> Bruce

SELECT name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
        AND month = 7 AND day = 29
        AND name IN (SELECT name FROM people
            JOIN bank_accounts ON people.id = bank_accounts.person_id
                WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60)
                    AND account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street'
                    AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
                    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25))
ORDER BY hour, minute LIMIT 1;


--slecting destination country based on the fact that he's taking the earliest flight

SELECT city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
AND month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1;

SELECT name FROM people WHERE phone_number = (SELECT receiver from phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = (SELECT name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
        AND month = 7 AND day = 29
        AND name IN (SELECT name FROM people
            JOIN bank_accounts ON people.id = bank_accounts.person_id
                WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60)
                    AND account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street'
                    AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
                    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25))
ORDER BY hour, minute LIMIT 1))
AND month = 7 AND day = 28 AND duration <= 60);

