select title from movies
where id in
(
    select a.movie_id from stars as a
    join stars as b
    where a.movie_id = b.movie_id
    and a.person_id in
    (
        select id from people
        where name = 'Bradley Cooper'
    )
    and b.person_id in
    (
        select id from people
        where name = 'Jennifer Lawrence'
    )
);
