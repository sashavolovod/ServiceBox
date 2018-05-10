--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.24
-- Dumped by pg_dump version 9.6.7

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: equipments; Type: TABLE; Schema: public; Owner: texac_admin
--

CREATE TABLE equipments (
    equipment_id integer NOT NULL,
    equipment_type_id integer NOT NULL,
    equipment_code integer NOT NULL,
    equipment_name character varying(128) NOT NULL
);


ALTER TABLE equipments OWNER TO texac_admin;

--
-- Name: equipments_equipment_id_seq; Type: SEQUENCE; Schema: public; Owner: texac_admin
--

CREATE SEQUENCE equipments_equipment_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE equipments_equipment_id_seq OWNER TO texac_admin;

--
-- Name: equipments_equipment_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: texac_admin
--

ALTER SEQUENCE equipments_equipment_id_seq OWNED BY equipments.equipment_id;


--
-- Name: equipments equipment_id; Type: DEFAULT; Schema: public; Owner: texac_admin
--

ALTER TABLE ONLY equipments ALTER COLUMN equipment_id SET DEFAULT nextval('equipments_equipment_id_seq'::regclass);


--
-- Data for Name: equipments; Type: TABLE DATA; Schema: public; Owner: texac_admin
--

COPY equipments (equipment_id, equipment_type_id, equipment_code, equipment_name) FROM stdin;
1	1	4499	СИ-500
2	1	4583	16Д25
3	1	4583	16Д25
4	1	13328	250ИТВМФ1
5	2	4868	ИТ-42
6	2	13329	Weiler E50
7	2	12904	Gildemeister CTX 400
8	2	7687	DMG CTX BETA 500
9	3	3636	6550
10	3	13062	6Т83Г-29
11	3	4118	6Т82-1
12	3	4710	6Т13Ф-1
13	3	4318	УС-32
14	3	13498	Vingrial 67R25PF2
15	3	7656	KF500
16	4	13138	MAF 45 TG
18	5	7667	Hermle C20
19	5	12985	UM 600
20	5	12988	UMS 900
21	5	3531	2Е460
22	5	4461	24К40СФ4
23	5	23502	Picomax 95
24	5	4690	WF72CH
25	5	4691	WF51D
26	5	12987	Mikron VF 32C
27	5	12737	Mikron VCE 1600
28	5	7603	VF-6
29	5	3479	VF-8
30	5	4188	PP4A
31	6	13464	7305ТД
32	6	891	7М37
33	6	12876	7Д36
34	7	13506	W-400А
35	7	13139	W-400НА
36	8	1257	3М636
37	8	845	3В642
38	8	3455	3В642
40	8	84	самодельный
41	8	4694	Saacke
42	8	4466	Ewag AG
43	8	4689	WS11SP
44	9	4694	Reinecker WZS-50
45	9	13449	Walter AG D-72072 Tubingen
46	9	12986	Ewamatic 106
47	9	7655	TTB
48	10	4772	3Д711АФ11
49	10	4610	3Д711АФ11
50	10	4539	3Д711АФ11
51	10	13273	3Д711ВФ11
52	10	4100	3Е711 В
53	10	4462	3Л722 В
54	10	4362	3Л722 В
55	10	13272	3Л722 ВК11
56	10	12816	ОШ426
57	10	4582	ОШ424Ф11М
58	10	12670	ОРША 4080
59	11	22365	ОРША-60200
60	12	3495	3М151В
61	12	4416	3М153АФ11
62	12	4693	S35
63	13	4363	3М227ВФ2
64	13	4569	3М227ВФ2
65	14	12683	3Е180В
66	15	4446	3951ВФ1
67	15	4756	PFS-30
68	16	13499	Mikromat 60S
69	16	7632	Hauser S45-40
70	16	4555	32К84СФ4
71	17	858	2Н135
72	17	3435	2Н135
73	17	4433	2532Л
74	17	13156	ОВР 50
75	17	3633	2411
76	17	12881	НС
77	17	13000	ГС-520
78	17	4315	ГР512
79	18	7612	Gamour
80	19	22832	Universal 1972
81	20	7670	НТС 300
82	21	1463	Remiremont ус. 63 т.
83	22	669	СН36х41
84	22	3439	СШЭ-6.6/7 М2
85	22	3426	СШЭ-6.6/7 М2
86	22	2621	Ц-105
87	22	4696	Natermer
88	22	3427	CН3-6-12.4/10
89	22	4697	Naberhterm
90	22	13259	RB 42/95
91	22	2628	10VPT.4022/24
92	22	3388	США 6.9/7
93	22	3480	LBA01-SE
94	22	23461	ПКС-50/12
95	22	23462	ПКС-50/12
96	22	23460	Элсит-80
98	24	12532	П326-02
99	24	416	Wilson
100	24	7051	Ванна промывочная
17	4	0	WHR 13 Q
97	23	22334	Ангара GPS505
39	8	4362	3Б632
\.


--
-- Name: equipments_equipment_id_seq; Type: SEQUENCE SET; Schema: public; Owner: texac_admin
--

SELECT pg_catalog.setval('equipments_equipment_id_seq', 2, true);


--
-- Name: equipments equipments_pkey; Type: CONSTRAINT; Schema: public; Owner: texac_admin
--

ALTER TABLE ONLY equipments
    ADD CONSTRAINT equipments_pkey PRIMARY KEY (equipment_id);


--
-- Name: equipments equipments_equipment_type_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: texac_admin
--

ALTER TABLE ONLY equipments
    ADD CONSTRAINT equipments_equipment_type_id_fkey FOREIGN KEY (equipment_type_id) REFERENCES equipment_types(equipment_types_id);


--
-- PostgreSQL database dump complete
--

