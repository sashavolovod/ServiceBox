create table equipment_users
(
    equipment_user_id serial primary key
    , equipment_user_name varchar(128) not null
    , equipment_user_position varchar(64) not null
    , ip_addr cidr not null
);


create table equipment_types
(
    equipment_types_id serial primary key not null 
    , equipment_type_name varchar(128) not null

);

create table equipments
(
    equipment_id serial primary key
    , equipment_type_id int references equipment_types(equipment_types_id) not null
	, equipment_code int not null
	, equipment_name varchar(128) not null 

);

create table equipment_services
(
    equipment_service_id serial primary key not null
    , equipment_services_date timestamp not null
    , status int not null default 0
);

create table equipment_service_details
(
    equipment_service_detail serial primary key not null
    , equipment_services_id int references equipment_services(equipment_service_id) not null 
    , equipment_users int references equipment_users(equipment_user_id) not null
    , note varchar(1024) not null
);
