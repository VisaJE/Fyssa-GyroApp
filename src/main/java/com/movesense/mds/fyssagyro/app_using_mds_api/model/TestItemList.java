package com.movesense.mds.fyssagyro.app_using_mds_api.model;


public class TestItemList {

    private final String name;

    public TestItemList(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    public String getName() {
        return name;
    }
}
