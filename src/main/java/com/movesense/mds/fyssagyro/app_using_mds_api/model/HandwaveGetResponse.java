package com.movesense.mds.fyssagyro.app_using_mds_api.model;

import com.google.gson.annotations.SerializedName;

public class HandwaveGetResponse {
    @SerializedName("Content")
    private final String content;


    public HandwaveGetResponse(String content){

        this.content = content;
    }

    public String getHandwave() {return this.content;}

}
