package com.movesense.mds.fyssagyro.app_using_mds_api.model;


import com.google.gson.annotations.SerializedName;

public class InfoAppResponse {

    @SerializedName("Content")
    private final Content mContent;

    public InfoAppResponse(Content content) {
        mContent = content;
    }

    public Content getContent() {
        return mContent;
    }

    public class Content {

        @SerializedName("name")
        private String name;

        @SerializedName("version")
        private String version;

        @SerializedName("company")
        private String company;

        public Content(String name, String version, String company) {
            this.name = name;
            this.version = version;
            this.company = company;
        }

        public String getName() {
            return name;
        }

        public String getVersion() {
            return version;
        }

        public String getCompany() {
            return company;
        }
    }

}
