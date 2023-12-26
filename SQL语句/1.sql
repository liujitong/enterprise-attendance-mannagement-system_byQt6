--员工编号（5位数字）、员工名（中文姓名或英文姓名）、登陆密码（8位以上）、部门、性别（从下拉列表选择“男”或“女”）、联系电话（11或12位数字组成）
CREATE TABLE employee (
    eno char(5) NOT NULL PRIMARY KEY,
    ename varchar(10) NOT NULL,
    dno char(3),
    gendar char(2),
    telephone char(12),
)
ALTER TABLE employee DROP CONSTRAINT enamecheck
--员工姓名只能是中文或英文
ALTER TABLE employee ADD CONSTRAINT enamecheck
CHECK (ename  not like '%[^吖-座]%|[^a-z]%|[^A-Z]%');
--性别只能是男或女
ALTER TABLE employee ADD CONSTRAINT sexcheck
CHECK (gendar IN ('男','女'));
--联系电话11或12位数字组成
ALTER TABLE employee ADD CONSTRAINT telcheck
CHECK (len(telephone) IN (11,12));
--员工编号5位数字
ALTER TABLE employee ADD CONSTRAINT enocheck1
CHECK (eno LIKE '[0-9][0-9][0-9][0-9][0-9]');

ALTER TABLE department ADD CONSTRAINT enocheck123
CHECK (dmano LIKE '[0-9][0-9][0-9][0-9][0-9]');

--登录密码八位以上:
ALTER TABLE account ADD CONSTRAINT psscheck
CHECK (len(code)>=8);

CREATE TABLE department(
    dno char(3)NOT NULL PRIMARY KEY,
    dname varchar(10) NOT NULL,
    dmano char(5) NOT NULL
)
--dname只能是中文
ALTER TABLE department ADD CONSTRAINT dnamecheck
CHECK (dname not like '%[^吖-座]%');

ALTER TABLE department DROP CONSTRAINT dnamecheck;
--dno长度为3
ALTER TABLE department ADD CONSTRAINT dnocheck
CHECK (len(dno)=3);

INSERT INTO account VALUES('%1','%2','2');

UPDATE account SET code='12345678' WHERE eno='00001';
--获取部门编号，名称，其员工数量，管理员姓名和备注
SELECT d.dno, d.dname, (SELECT COUNT(*) FROM employee WHERE dno = d.dno) AS '员工数量', e.ename AS '管理员姓名', d.Other AS '备注'
FROM department d
LEFT JOIN employee e ON d.dmano = e.eno
GROUP BY d.dno, d.dname, e.ename, d.Other;
GO
CREATE TRIGGER insert_employee
ON employee
FOR INSERT
AS
BEGIN
    INSERT INTO account VALUES((SELECT eno FROM inserted),'12345678','2');
END
GO
--设计一个触发器，当删除一个员工的时候，自动删除其账户
CREATE TRIGGER delete_employee
ON employee
FOR DELETE
AS
BEGIN
    DELETE FROM account WHERE eno=(SELECT eno FROM deleted);
END
Go
--设计触发器，当删除一个部门的时候，将其员工的部门编号置为空，将部门管理员置的类型置为普通员工
CREATE TRIGGER delete_department
ON department
FOR DELETE
AS
BEGIN
    UPDATE employee SET dno=NULL WHERE dno=(SELECT dno FROM deleted);
    UPDATE account SET type='2' WHERE eno=(SELECT dmano FROM deleted);
END
GO
--将部门编号为002的部门管理员的类型设置为普通员工
UPDATE account SET type='2' WHERE eno=(SELECT dmano FROM department WHERE dno='002');
GO
--设计触发器，当部门被修改的时候，将部门管理员的dno置为修改后的部门编号
CREATE TRIGGER update_department
ON department
FOR UPDATE
AS
BEGIN
    UPDATE employee SET dno=(SELECT dno FROM inserted) WHERE eno=(SELECT dmano FROM deleted);
END
GO
--删除指定编号的部门
DELETE FROM department WHERE dno='002';

--找出所有部门为空的员工
SELECT * FROM employee WHERE dno IS NULL;