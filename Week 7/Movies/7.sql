select a.title, b.rating
from movies as a
join ratings as b
on a.id = b.movie_id
where a.year = 2010
order by b.rating desc, a.title 
