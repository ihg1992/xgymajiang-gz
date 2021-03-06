﻿#include "table_delegate.h"
#include "log.h"
#include "table.h"
#include "zjh.h"
#include <json/json.h>

extern ZJH zjh;
extern Log mjlog;

TableDelegate *TableDelegate::m_pdl = NULL;

TableDelegate *TableDelegate::getInstance()
{
    if (m_pdl == NULL)
    {
        m_pdl = new TableDelegate();
    }

    return m_pdl;
}

Table *TableDelegate::getTable()
{
    Table *table = new Table();
    return table;
}

int TableDelegate::init_table(Table *table, int i)
{
    int vid = zjh.conf["tables"]["vid"].asInt();
    int zid = zjh.conf["tables"]["zid"].asInt();
    int type = zjh.conf["tables"]["table_type"].asInt();
    float fee = atof(zjh.conf["tables"]["fee"].asString().c_str());
    int min_money = zjh.conf["tables"]["min_money"].asInt();
    int max_money = zjh.conf["tables"]["max_money"].asInt();
    int base_money = zjh.conf["tables"]["base_money"].asInt();
    int base_ratio = zjh.conf["tables"]["base_ratio"].asInt();
    int min_round = zjh.conf["tables"]["min_round"].asInt();
    int max_round = zjh.conf["tables"]["max_round"].asInt();

    int ret = table->init(i, vid, zid, type, fee, min_money, max_money, base_money, base_ratio, min_round, max_round);
    return ret;
}

void TableDelegate::handler_net_status(Table *table, Player *player, int status)
{
    table->handler_net_status(player, status);
}

int TableDelegate::handler_login(Table *table, Player *player)
{
    return table->handler_login(player);
}

int TableDelegate::handler_login_succ_uc(Table *table, Player *player)
{
    return table->handler_login_succ_uc(player);
}

int TableDelegate::handler_table_info(Table *table, Player *player)
{
    return table->handler_table_info(player);
}

int TableDelegate::handler_logout(Table *table, Player *player)
{
    return table->handler_logout(player);
}

int TableDelegate::del_player(Table *table, Player *player)
{
    return table->del_player(player);
}

int TableDelegate::handler_cmd(Table *table, int cmd, Player *player)
{
    return table->handler_cmd(cmd, player);
}

int TableDelegate::get_tid(Table *table)
{
    return table->tid;
}

int TableDelegate::get_ttid(Table *table)
{
    return table->ttid;
}

int TableDelegate::get_state(Table *table)
{
    return table->state;
}

std::map<int, Player *> *TableDelegate::get_players(Table *table)
{
    return &table->players;
}

int TableDelegate::get_ts(Table *table)
{
    return table->ts;
}

void TableDelegate::clean_table(Table *table)
{
    table->clean_table();
}

void TableDelegate::set_ttid(Table *table, int ttid)
{
    table->ttid = ttid;
}

void TableDelegate::set_state(Table *table, int state)
{
    if (state == ROOM_WAIT_GAME)
    {
        table->state = ROOM_WAIT_GAME;
    }
    else if (state == END_GAME)
    {
        table->state = END_GAME;
    }
    else if (state == READY)
    {
        table->state = READY;
    }
}

void TableDelegate::set_owner_uid(Table *table, int uid)
{
    table->owner_uid = uid;
}

void TableDelegate::init_table_type(Table *table, Json::Value &val, int robot)
{

    if (robot == 1)
    {
        int has_feng = 0;
        int has_ghost = 1;
        int horse_num = 1;
        int table_type = zjh.conf["tables"]["type"].asInt();
        int hu_pair = 1;
        int max_play_count = 8;
        int ping_hu_fang_pao = 1;
        int dead_double = 0;
        int ben_ji = 0;     //本鸡
        int wu_gu_ji = 0;   //乌骨鸡
        int bao_ji = 0;     //包鸡
       // int huan_san_zhang = 0;
        int is_lian_zhuang = 0;
        int is_fang_ji = 0; //0不是翻鸡  1是翻鸡 2滚滚鸡
            //int substitute = 0;
        int cost_select_flag = 1;
        int is_man_tang_ji = 1;

        int jin_yin_ji = 0;  //金银鸡
        int chui_feng_ji = 0;//吹风鸡
        int xing_qi_ji = 0; //星期鸡
        int shu_zi_ji = 0;   //数字鸡
        int jian_qi_wa = 0;  //见七挖

        int gui_yang = 1; //1贵阳  2 二丁 3 三丁
        int lai_zi_ji = 0; //癞子鸡
        int zha_niao = 0; //扎鸟
        table->init_table_type(table_type, has_ghost, has_feng, hu_pair, horse_num, max_play_count, ping_hu_fang_pao, dead_double, cost_select_flag, ben_ji, wu_gu_ji, bao_ji, is_fang_ji, is_man_tang_ji, jin_yin_ji, chui_feng_ji, xing_qi_ji, shu_zi_ji, jian_qi_wa, gui_yang, lai_zi_ji, zha_niao , is_lian_zhuang);
    }
    else
    {
        int has_feng = 0;
        int has_ghost = 1;
        int horse_num = val["horse_num"].asInt();
        int table_type = zjh.conf["tables"]["type"].asInt();
        int hu_pair = 1;
        int max_play_count = val["max_play_count"].asInt();
        int ping_hu_fang_pao = val["fang_pao"].asInt();

        int dead_double = 0;
        int substitute = 0;
        int forbid_same_ip = 0;
        int forbid_same_place = 0;
        int ben_ji = val["ben_ji"].asInt();                 //本鸡
        int wu_gu_ji = val["wu_gu_ji"].asInt();             //乌骨鸡
        int bao_ji = val["bao_ji"].asInt();                 //包鸡
      //  int huan_san_zhang = val["huan_san_zhang"].asInt(); //换三张
        int is_fang_ji = val["is_fang_ji"].asInt();         //0不是翻鸡  1是翻鸡 2滚滚鸡
        int is_man_tang_ji = val["is_man_tang_ji"].asInt(); //1, 满堂鸡 2 手上鸡

        int jin_yin_ji = val["jin_yin_ji"].asInt();  //金银鸡
        int chui_feng_ji = val["chui_feng_ji"].asInt();//吹风鸡
        int xing_qi_ji = val["xing_qi_ji"].asInt(); //星期鸡
        int shu_zi_ji = val["shu_zi_ji"].asInt();   //数字鸡
        int jian_qi_wa = val["jian_qi_wa"].asInt();  //见七挖

        int gui_yang = val["gui_yang"].asInt(); //1贵阳  2 二丁 3 三丁
        int lai_zi_ji = val["lai_zi_ji"].asInt(); //癞子鸡
        int zha_niao = val["zha_niao"].asInt(); //扎鸟
        int is_lian_zhuang = val["is_lian_zhuang"].asInt();
        if (!val["forbid_same_ip"].isNull())
        {
            forbid_same_ip = val["forbid_same_ip"].asInt();
        }

        if (!val["forbid_same_place"].isNull())
        {
            forbid_same_place = val["forbid_same_place"].asInt();
        }

        int cost_select_flag = 1;
        if (!val["cost_select_flag"].isNull())
        {
            cost_select_flag = val["cost_select_flag"].asInt();
        }

        if (!val["dead_double"].isNull())
        {
            dead_double = val["dead_double"].asInt();
        }

        if (!val["substitute"].isNull())
        {
            substitute = val["substitute"].asInt();
        }

        table->config_of_replay = val;
        table->init_table_type(table_type, has_ghost, has_feng, hu_pair, horse_num, max_play_count, ping_hu_fang_pao, dead_double,
                               forbid_same_ip, forbid_same_place, substitute, cost_select_flag, ben_ji, wu_gu_ji, bao_ji , is_fang_ji, is_man_tang_ji, jin_yin_ji, chui_feng_ji, xing_qi_ji, shu_zi_ji, jian_qi_wa, gui_yang, lai_zi_ji, zha_niao, is_lian_zhuang);
    }
}

int TableDelegate::init_deck(int type)
{
    HoleCards::register_type_handler(CARD_TYPE_PING_HU, 12);          //1分
    HoleCards::register_type_handler(CARD_TYPE_PENG_HU, 11);          //5分
    HoleCards::register_type_handler(CARD_TYPE_QI_XIAO_DUI, 10);      //10分
    HoleCards::register_type_handler(CARD_TYPE_QING_YI_SE, 9);       //10分
    HoleCards::register_type_handler(CARD_TYPE_JIN_GOU_DIAO, 8);       //10分
    HoleCards::register_type_handler(CARD_TYPE_QING_PENG, 7);        //15分
    HoleCards::register_type_handler(CARD_TYPE_JIANG_JIN_GOU_DIAO, 6);        //15分
    HoleCards::register_type_handler(CARD_TYPE_LONG_QI_DUI, 5);      //20分
    HoleCards::register_type_handler(CARD_TYPE_QING_QI_DUI, 4);      //20分
    HoleCards::register_type_handler(CARD_TYPE_QING_JIN_GOU_DIAO, 3);      //20分
    HoleCards::register_type_handler(CARD_TYPE_QING_PENG_JIN_GOU_DIAO, 2);        //25分
    HoleCards::register_type_handler(CARD_TYPE_QING_LONG_QI_DUI, 1); //30分
    return 0;
}

int TableDelegate::get_max_players(Table *table)
{
    return table->max_ready_players;
}

int TableDelegate::get_ahead_start(Table *table)
{
    return table->ahead_start_flag;
}

int TableDelegate::set_create_rmb(Table *table, int rmb, int aarmb)
{
    return table->set_create_rmb(rmb, aarmb);
}
int TableDelegate::get_create_rmb(Table *table)
{
    return table->create_rmb;
}

int TableDelegate::get_cost_select_flag(Table *table)
{
    return table->cost_select_flag;
}

int TableDelegate::permit_join(Table *table, Player *player)
{
    return table->permit_join(player);
}

int TableDelegate::get_rmb_num(int play_board)
{
    int base_play_board = zjh.conf["tables"]["base_board"].asInt();
    base_play_board = base_play_board <= 0 ? 8 : base_play_board;
    int ratio = play_board / base_play_board;
    ratio = std::max(1, ratio);
    return ratio;
}

int TableDelegate::get_substitute_flag(Table *table)
{
    return table->substitute;
}

void TableDelegate::handler_dismiss_table(Table *table)
{
    table->handler_owner_dismiss_table();
}
