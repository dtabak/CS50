-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check out the crime scene reports // Findings: 10:15am crime time, three witnesses
select * from crime_scene_reports
where year = 2021
and month = 07
and day = 28
and street = 'Humphrey Street';

-- Check out the interviews with witnesses // Findings: Interviewee Names: Ruth, Eugene, Raymond
-- flight the next day purchased by the other person on the phone
-- the thief withdrew money from atm on the Leggett Street earlier that morning
select * from interviews
where year = 2021
and month = 07
and day = 28;

-- Check out the atm transactions
select * from atm_transactions
where year = 2021
and month = 07
and day = 28
and atm_location = 'Leggett Street'
and transaction_type = 'withdraw';

-- Find out account holder's names // Findings Benista, Brooke, Bruce, Diana, Iman, Kenny, Luca, Taylor
select name from people
where id in (
select person_id from bank_accounts
where account_number in
(
    select account_number from atm_transactions
where year = 2021
and month = 07
and day = 28
and atm_location = 'Leggett Street'
and transaction_type = 'withdraw'
)
)
order by name;

-- Check out the bakery security logs within the 10 minutes timeframe of crime time
select * from bakery_security_logs
where year = 2021
and month = 07
and day = 28
and hour = 10
and minute >= 15 and minute <= 25;

-- Find people who are the title holders for these license plates // Findings Barry, Bruce, Diana, Iman, Kelsey,
-- Luca, Sofia, Vanessa

select name
from people
where license_plate in
(
    select license_plate from bakery_security_logs
where year = 2021
and month = 07
and day = 28
and hour = 10
and minute >= 15 and minute <= 25
)
order by name;

-- Find out the names in the intersection of bank account holders and license plate holders // Findings
-- Common names: Iman, Luca, Diana, Bruce

select name from people
where id in (
select person_id from bank_accounts
where account_number in
(
    select account_number from atm_transactions
where year = 2021
and month = 07
and day = 28
and atm_location = 'Leggett Street'
and transaction_type = 'withdraw'
)
)
and license_plate in
(
    select license_plate from bakery_security_logs
where year = 2021
and month = 07
and day = 28
and hour = 10
and minute >= 15 and minute <= 25
);

-- Explore phone calls occurred at the event time
select *
from phone_calls
where year = 2021
and month = 07
and day = 28
and duration <= 60;

-- Filter people by phone number // Findings: Diana, Bruce (potential thiefs)

select name from people
where id in (
select person_id from bank_accounts
where account_number in
(
    select account_number from atm_transactions
where year = 2021
and month = 07
and day = 28
and atm_location = 'Leggett Street'
and transaction_type = 'withdraw'
)
)
and license_plate in
(
    select license_plate from bakery_security_logs
where year = 2021
and month = 07
and day = 28
and hour = 10
and minute >= 15 and minute <= 25
)
and phone_number in
(
    select caller
from phone_calls
where year = 2021
and month = 07
and day = 28
and duration <= 60
);

-- Check out the airports

select * from airports
where city = 'Fiftyville';

-- Check out flights departed from this airport on the next day of the crime
-- Find out the departure city of the earliest flight (aka where the thief escaped to)

select city from airports
where id in (

select destination_airport_id from flights
where origin_airport_id in
(
    select id from airports
where city = 'Fiftyville'
)
and year = 2021
and month = 07
and day = 29
order by hour, minute
limit 1
);

-- Check out the passengers on that flight

select passport_number from passengers
where flight_id in
(
    select id from flights
where origin_airport_id in
(
    select id from airports
where city = 'Fiftyville'
)
and year = 2021
and month = 07
and day = 29
order by hour, minute
limit 1
);

-- Filter the potential thief list by passport numbers from that flight // Findings: Bruce is the thief

select name from people
where id in (
select person_id from bank_accounts
where account_number in
(
    select account_number from atm_transactions
where year = 2021
and month = 07
and day = 28
and atm_location = 'Leggett Street'
and transaction_type = 'withdraw'
)
)
and license_plate in
(
    select license_plate from bakery_security_logs
where year = 2021
and month = 07
and day = 28
and hour = 10
and minute >= 15 and minute <= 25
)
and phone_number in
(
    select caller
from phone_calls
where year = 2021
and month = 07
and day = 28
and duration <= 60
)
and passport_number in
(
    select passport_number from passengers
where flight_id in
(
    select id from flights
where origin_airport_id in
(
    select id from airports
where city = 'Fiftyville'
)
and year = 2021
and month = 07
and day = 29
order by hour, minute
limit 1
)
);

-- Find out the name of the receiver of phone call from Bruce (the thief) occurred at the event time
select name
from people
where phone_number in (
    select receiver
from phone_calls
where year = 2021
and month = 07
and day = 28
and duration <= 60
and caller in
(
    select phone_number from people where name = 'Bruce'
)
);




