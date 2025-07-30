#include <gtest/gtest.h>
#include <memorial/SoldierEntry.h>
/*SoldierEntry passport_soldier{
    "Шестак",               //
    "Иван",                 // И.  NULL
    "Яковлевич",            // Я.  NULL
    "/Возраст",             // NULL
    "",
    "",
    "",
    "ст. лейтенант",
    "",
    "03.08.1943",           // NULL
    "Орловская обл. Залегощенский р-н, д. Павлово, братская могила",
    "",
    "",
    "",
    "",
    "https://obd-memorial.ru/html/info.htm?id=89519636",
    ""};
SoldierEntry vedomost_soldier{
    "Шестак",
    "Иван",
    "Яковлевич",
    "/Возраст",
    "",
    "",
    "",
    "ст. лейтенант",
    "",
    "03.08.1943",
    "Орловская обл. Залегощенский р-н, д. Павлово, братская могила",
    "",
    "",
    "",
    "",
    "https://obd-memorial.ru/html/info.htm?id=89519636",
    ""};*/


TEST(CompareFIO, LastName) {
    {
        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак.,!"));
        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", compare_utils::Strip("Шестак.,!")));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак    "));
        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", compare_utils::Strip("Шестак    ")));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак.,!   "));
        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", compare_utils::Strip("Шестак.,!   ")));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак   .,!"));
        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", compare_utils::Strip("Шестак   .,!")));

        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шес"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шес."));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Ш."));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Ш.   "));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "NULL"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Null"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "null"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Null. ! "));

        EXPECT_TRUE(compare_utils::CompareLastName("Шестак", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак.,!"));
        EXPECT_TRUE(compare_utils::CompareLastName(compare_utils::Strip("Шестак.,!"), "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак    "));
        EXPECT_TRUE(compare_utils::CompareLastName(compare_utils::Strip("Шестак    "), "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак.,!   "));
        EXPECT_TRUE(compare_utils::CompareLastName(compare_utils::Strip("Шестак.,!   "), "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шестак", "Шестак   .,!"));
        EXPECT_TRUE(compare_utils::CompareLastName(compare_utils::Strip("Шестак   .,!"), "Шестак"));

        EXPECT_FALSE(compare_utils::CompareLastName("Шес", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Шес.", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Ш.", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Ш.   ", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("NULL", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Null", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("null", "Шестак"));
        EXPECT_FALSE(compare_utils::CompareLastName("Null. !  ", "Шестак"));
    }
}

TEST(CompareFIO, FirstName) {
    {
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван.,!"));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("Иван.,!")));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван    "));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("Иван    ")));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван.,!   "));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("Иван.,!   ")));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван   .,!"));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("Иван   .,!")));

        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Ива"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Ива."));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "И."));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("И.")));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "И.   "));
        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", compare_utils::Strip("И.   ")));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "NULL"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Null"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "null"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Null. ! "));

        EXPECT_TRUE(compare_utils::CompareFirstName("Иван", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван.,!"));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("Иван.,!"), "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван    "));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("Иван    "), "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван.,!   "));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("Иван.,!   "), "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Иван", "Иван   .,!"));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("Иван   .,!"), "Иван"));

        EXPECT_FALSE(compare_utils::CompareFirstName("Ива", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Ива.", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("И.", "Иван"));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("И."), "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("И.   ", "Иван"));
        EXPECT_TRUE(compare_utils::CompareFirstName(compare_utils::Strip("И.   "), "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("NULL", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Null", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("null", "Иван"));
        EXPECT_FALSE(compare_utils::CompareFirstName("Null. !  ", "Иван"));
    }
}

TEST(CompareFIO, Patronimic) {
    {
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич.,!"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Яковлевич.,!")));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич    "));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Яковлевич    ")));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич.,!   "));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Яковлевич.,!   ")));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич   .,!"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Яковлевич   .,!")));

        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яко"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яко."));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Я."));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Я.")));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Я.   "));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Я.   ")));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", "NULL"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", "Null"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", "null"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Null. ! "));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", compare_utils::Strip("Null. ! ")));

        EXPECT_TRUE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич.,!"));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Яковлевич.,!"), "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич    "));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Яковлевич    "), "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич.,!   "));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Яковлевич.,!   "), "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яковлевич", "Яковлевич   .,!"));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Яковлевич   .,!"), "Яковлевич"));

        EXPECT_FALSE(compare_utils::ComparePatronimic("Яко", "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Яко.", "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Я.", "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Я."), "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Я.   ", "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Я.   "), "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("NULL", "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("Null", "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic("null", "Яковлевич"));
        EXPECT_FALSE(compare_utils::ComparePatronimic("Null. !  ", "Яковлевич"));
        EXPECT_TRUE(compare_utils::ComparePatronimic(compare_utils::Strip("Null. !  "), "Яковлевич"));
    }
}

TEST(CompareBirthdate, DateCtor) { {
        compare_utils::Date date{"10.10.1900"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"10.10.190"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 190);
    } {
        compare_utils::Date date{"10.1.1900"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 1);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"1.10.1900"};
        EXPECT_EQ(date.day, 1);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"01.10.1900"};
        EXPECT_EQ(date.day, 1);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"10.01.1900"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 1);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"10.__.1900"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"__.10.1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"__.__.1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    }

    // Другие странные ситуации
    {
        compare_utils::Date date{"__/__/1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"__-__-1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"__-__/1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"10-__/1900"};
        EXPECT_EQ(date.day, 10);
        EXPECT_EQ(date.month, 0);
        EXPECT_EQ(date.year, 1900);
    } {
        compare_utils::Date date{"__-10/1900"};
        EXPECT_EQ(date.day, 0);
        EXPECT_EQ(date.month, 10);
        EXPECT_EQ(date.year, 1900);
    }
}

TEST(CompareBirthdate, DateComparator) { {
        compare_utils::Date date1{"10.10.1900"};
        compare_utils::Date date2{"10.10.1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"__.__.1900"};
        compare_utils::Date date2{"__.__.1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"1900"};
        compare_utils::Date date2{"1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"__.__.1900"};
        compare_utils::Date date2{"1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"__.__.1900"};
        compare_utils::Date date2{"11.10.1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"10.__.1900"};
        compare_utils::Date date2{"10.10.1900"};
        EXPECT_EQ(date1, date2);
    } {
        compare_utils::Date date1{"10.10.1900"};
        compare_utils::Date date2{"11.10.1900"};
        EXPECT_NE(date1, date2);
    } {
        compare_utils::Date date1{"10.10.1900"};
        compare_utils::Date date2{"10.11.1900"};
        EXPECT_NE(date1, date2);
    } {
        compare_utils::Date date1{"10.10.1900"};
        compare_utils::Date date2{"10.10.1901"};
        EXPECT_NE(date1, date2);
    } {
        compare_utils::Date date1{"1900"};
        compare_utils::Date date2{"1901"};
        EXPECT_NE(date1, date2);
    }
}

TEST(CompareBirthdate, BirthdateComparator) {
    EXPECT_TRUE(compare_utils::CompareBirthdate("10.10.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10.__.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("__.10.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("__.__.1900", "__.__.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("/Возраст", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "NULL"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("/Возраст", "/Возраст"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("/Возраст", "1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "__.__.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("/Возраст", "__.__.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10-10/1900", "10,10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10-__0/1900", "__.0/1900"));

    EXPECT_FALSE(compare_utils::CompareBirthdate("9.10.1900", "10.10.1900"));
    EXPECT_FALSE(compare_utils::CompareBirthdate("09.10.1900", "10.10.1900"));
}


TEST(CompareLossDate, CompareLossDate) {
    EXPECT_TRUE(compare_utils::CompareBirthdate("10.10.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10.__.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("__.10.1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("__.__.1900", "__.__.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("1900", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "10.10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "NULL"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("NULL", "__.__.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10-10/1900", "10,10.1900"));
    EXPECT_TRUE(compare_utils::CompareBirthdate("10-__0/1900", "__.0/1900"));

    EXPECT_FALSE(compare_utils::CompareBirthdate("9.10.1900", "10.10.1900"));
    EXPECT_FALSE(compare_utils::CompareBirthdate("09.10.1900", "10.10.1900"));
}

TEST(CompareMilitaryRank, CompareMilitaryRank) {
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("рядовой", "рядовой"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ряд", "рядовой"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ряд.", "рядовой"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("рядовой", "красноармеец"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ефрейтор", "Ефрейтор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ефр", "Ефрейтор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ефр.", "Ефрейтор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ефрейтор", "Ефрейтор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("младший сержант", "младший сержант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл.сержант", "младший сержант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл. сержант", "младший сержант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл.   сержант", "младший сержант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл.лейтенант", "младший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл. лейтенант", "младший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("мл.   лейтенант", "младший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ст.лейтенант", "старший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ст. лейтенант", "старший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("ст.   лейтенант", "старший лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("лейтенант", "лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("л-т", "лейтенант"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("к-н", "капитан"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("капитан", "капитан"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("майор", "Майор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("м-Р", "Майор"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("подполковник", "Подполковник"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("п/п-к", "подполковник"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("полковник", "Полковник"));
    EXPECT_TRUE(compare_utils::CompareMilitaryRank("п-к", "полковник"));
}


TEST(CompareBurialPlace, BurialPlaceCtor) {
    compare_utils::BurialPlace bp = compare_utils::BurialPlace(
        "Орловская обл.,  Залегощенский р-н, Н.-Залегощенский с/с, д. Гвоздяное");
    std::unordered_map<std::string, std::string> places = {
        {"область", "орловская"},
        {"район", "залегощенский"},
        {"сельсовет", "н.-залегощенский"},
        {"деревня", "гвоздяное"},
    };
    compare_utils::BurialPlace bp2 = compare_utils::BurialPlace(
        "Орловская обл.,     Залегощенский    Р-н, Н.-Залегощенский с/с, д. Гвоздяное");
    EXPECT_EQ(bp.places_, places);
    EXPECT_EQ(bp, bp2);

    bp = compare_utils::BurialPlace(
        "г. Москва, шоссе Ногинское, д. 4, кв. 6");
    places = {
        {"город", "москва"},
        {"шоссе", "ногинское"},
        {"деревня", "4"},
        {"квартира", "6"},
    };
    EXPECT_EQ(bp.places_, places);
}


TEST(CompareBurialPlace, CompareBurialPlace) {
    {
        compare_utils::BurialPlace bp1{"Орловская обл.,  Залегощенский р-н, Н.-Залегощенский с/с, д. Гвоздяное"};
        compare_utils::BurialPlace bp2{"Орловская обл.,  Залегощенский район, Н.-Залегощенский с/с, деревня. Гвоздяное"};
        EXPECT_EQ(bp1, bp2);
    }
}

TEST(CompareUtils, RemoveSpaces_Orlovskaya) {
    EXPECT_EQ(compare_utils::RemoveSpaces("Орловская обл., Залегощенский р-н, д. Павлово, братская могила"),
              "Орловскаяобл.,Залегощенскийр-н,д.Павлово,братскаямогила");
    EXPECT_EQ(compare_utils::RemoveSpaces("   "), "");
    EXPECT_EQ(compare_utils::RemoveSpaces("д. Ивановка"), "д.Ивановка");
    EXPECT_EQ(compare_utils::RemoveSpaces("Орловская обл. Мценский р-н"), "Орловскаяобл.Мценскийр-н");
}

// =============================================================
