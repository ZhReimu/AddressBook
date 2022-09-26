create table students
(
    sid      INTEGER PRIMARY KEY AUTOINCREMENT,
    name     TEXT,
    address  TEXT,
    phone    INTEGER CHECK ( length(phone) >= 8 ),
    postCode INTEGER CHECK ( length(0 + postCode) = length(postCode) ),
    email    TEXT CHECK ( instr(email, '@') != 0 )
);