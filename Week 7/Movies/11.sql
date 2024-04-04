select title from movies as m
join ratings as r
on r.movie_id = m.id
where m.id in
(
    select movie_id from stars
    where person_id in
    (
        select id from people
        where name = 'Chadwick Boseman'

    )
)
order by r.rating desc
limit 5;
