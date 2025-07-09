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