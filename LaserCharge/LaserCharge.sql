
-- Table: province
CREATE TABLE province ( 
    abbr VARCHAR( 12 )  PRIMARY KEY
                        NOT NULL,
    name VARCHAR( 64 )  NOT NULL,
    date DATETIME 
);

INSERT INTO [province] ([abbr], [name], [date]) VALUES ('sds', 'ɽ��ʡ', '2017-11-09 15:22:54');
INSERT INTO [province] ([abbr], [name], [date]) VALUES ('jxs', '����ʡ', '2017-11-10 10:51:47');

-- Table: city
CREATE TABLE city ( 
    abbr     VARCHAR( 12 )  PRIMARY KEY
                            NOT NULL,
    name     VARCHAR( 64 )  NOT NULL,
    province VARCHAR( 12 ),
    date     DATETIME 
);

INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('yts', '��̨��', 'sds', '2017-11-09 15:24:43');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cds', '������', 'sds', '2017-11-09 15:26:44');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('njs', '������', 'sds', '2017-11-09 16:50:27');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('qds', '�ൺ��', 'sds', '2017-11-09 17:01:59');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('zcs', '֪ӿ��', 'sds', '2017-11-09 17:04:24');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('txm', '������', 'sds', '2017-11-09 17:04:37');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('tas', '̩����', 'sds', '2017-11-09 17:17:07');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('lhs', '�ٻ���', 'sds', '2017-11-09 17:17:19');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('ths', '�캫��', 'sds', '2017-11-09 17:17:28');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('dts', '��ͬ��', 'sds', '2017-11-09 17:17:35');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('dys', '��Ӫ��', 'sds', '2017-11-10 11:16:02');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('hzs', '������', 'sds', '2017-11-10 11:16:11');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('lzs', '������', 'sds', '2017-11-10 11:16:23');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('jms', '��ī��', 'sds', '2017-11-10 11:16:34');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('wfs', 'Ϋ����', 'sds', '2017-11-10 11:16:41');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('zbs', '�Ͳ���', 'sds', '2017-11-10 11:16:53');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('lys', '������', 'sds', '2017-11-10 11:17:20');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('lks', '������', 'sds', '2017-11-10 11:17:37');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('nts', '��ͨ��', 'sds', '2017-11-10 11:27:40');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs1', '����1', 'sds', '2017-11-10 15:07:47');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs2', '����2', 'sds', '2017-11-10 15:07:54');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs3', '����3', 'sds', '2017-11-10 15:08:01');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs4', '����4', 'sds', '2017-11-10 15:08:05');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs5', '����5', 'sds', '2017-11-10 15:08:09');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs6', '����6', 'sds', '2017-11-10 15:08:14');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs7', '����7', 'sds', '2017-11-10 15:08:18');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('cs8', '����8', 'sds', '2017-11-10 15:08:22');
INSERT INTO [city] ([abbr], [name], [province], [date]) VALUES ('jztjy', '���ݴ��Ժ', 'sds', '2017-11-10 16:09:04');

-- Table: cinema
CREATE TABLE cinema ( 
    abbr VARCHAR( 48 )   PRIMARY KEY
                         NOT NULL,
    name VARCHAR( 128 )  NOT NULL,
    city VARCHAR( 12 )   NOT NULL,
    date DATETIME 
);

INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('ddsz��ls��', '������֣���ɽ��', 'cds', '2017-11-09 15:45:22');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('mtfs', '���츣ɽ', 'cds', '2017-11-09 15:45:43');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('fsjy', '��ɽ��Ժ', 'yts', '2017-11-10 13:39:39');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('cszj', '����֮��', 'yts', '2017-11-10 13:39:51');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('xldy', 'С�Ե�Ӱ', 'njs', '2017-11-10 14:57:16');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('md1', '���1', 'njs', '2017-11-10 14:57:29');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('bl1', '����1', 'njs', '2017-11-10 14:57:35');
INSERT INTO [cinema] ([abbr], [name], [city], [date]) VALUES ('jztjy', '���ݴ��Ժ', 'qds', '2017-11-10 16:09:22');

-- Table: device
CREATE TABLE device ( 
    ID         VARCHAR( 24 )   PRIMARY KEY
                               NOT NULL,
    cinema     VARCHAR( 48 )   NOT NULL,
    TotalHours REAL            NOT NULL,
    memo       VARCHAR( 512 ),
    date       DATETIME 
);

INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('2.22222222222222e+23', 'fsjy', 0.0, '�౱�������������豸', '2017-11-10 14:40:09');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('3.33333333333333e+23', 'fsjy', 0.0, '�����豸', '2017-11-10 14:42:20');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('91820123abe2aa2323a12222', 'bl1', 0.0, '�豸����', '2017-11-10 14:58:00');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('4.44444444444444e+23', 'fsjy', 0.0, '', '2017-11-10 16:09:41');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('5.55555555555556e+23', 'fsjy', 0.0, '', '2017-11-10 16:09:51');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('6.66666666666667e+23', 'fsjy', 0.0, '', '2017-11-10 16:10:01');
INSERT INTO [device] ([ID], [cinema], [TotalHours], [memo], [date]) VALUES ('1.11111111111111e+23', 'fsjy', 0.0, '', '2017-11-10 16:10:06');

-- Table: data
CREATE TABLE data ( 
    ID          VARCHAR( 24 )   PRIMARY KEY
                                NOT NULL,
    UUID        VARCHAR( 48 )   UNIQUE,
    ChargeHours REAL            NOT NULL,
    ValidBefore DATETIME        NOT NULL,
    memo        VARCHAR( 512 ),
    date        DATETIME 
);

INSERT INTO [data] ([ID], [UUID], [ChargeHours], [ValidBefore], [memo], [date]) VALUES (22222222222, '{7d81d868-5d33-4497-8367-0740e7cb5e59}', 100.2, '2017-11-02 12:12:30', 'no memo', '2017-11-12 08:08:19');
