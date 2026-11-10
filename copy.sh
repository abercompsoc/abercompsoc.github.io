rm -rf /var/www/*
cp -r ./site/* /var/www/
chown -R $USER /var/www/

rm -rf /var/blogs/*
cp -r ./blogs/* /var/blogs/
chown -R $USER /var/blogs/

sudo sv restart nginx
