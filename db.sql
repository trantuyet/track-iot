create database iot;
use iot;

create table sim_info (
id bigint not null auto_increment, 
system_mode varchar(20),
operation_mode varchar(20),
mcc varchar(3),
mcn varchar(3),
p_cell_id varchar(64),
frequency_band varchar(12),
earfcn int,
dlbw int,
ulbw int,
rsrp int,
rsrq int,
created_at timestamp default now(),
updated_at timestamp default null,
primary key (id)
 );
 
create table users (
id bigint not null auto_increment,
username varchar(30),
email varchar(256),
user_password varchar(64),
is_active bit,
role_id tinyint(3),
created_at timestamp default now(),
updated_at timestamp,
primary key (id)
);

create table roles (
id bigint not null auto_increment,
role varchar(64),
created_at timestamp default now(),
updated_at timestamp,
primary key (id)
);

create table user_has_role (
id bigint not null auto_increment,
user_id bigint,
role_id bigint,
PRIMARY KEY (id),
FOREIGN KEY (user_id) REFERENCES users(id),
FOREIGN KEY (role_id) REFERENCES roles(id)
);

insert into roles (role) values
( 'client'
),
('admin');

insert into users (username, email, user_password, is_active, role_id) values
( 'trantuyet', 'trantuyet.dev@gmail.com', '$2y$10$7sUw40Y529gy6zpITffRTevz3eMJE8iM1C207jHZbr5GMCiKklAmK', 1, 2
),
('testclient', 'demo@gmail.com', '$2y$10$jjQ4/zADRe9jVRLjSvA7wuhzwyVwIiWyoJQyHxKm7QHOIk5cRPRyy', 1, 1);

insert into user_has_role (user_id, role_id) values 
(1,2), (2,1);

insert into sim_info (system_mode, operation_mode, mcc, mcn, p_cell_id, frequency_band, earfcn, dlbw 
, ulbw 
, rsrp 
, rsrq) values
('fakeSM', 'fakeOPM', '452', '04', 'fakePCI', 1200, 12, 23, 34, 33, 100);