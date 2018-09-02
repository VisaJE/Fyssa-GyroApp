package com.movesense.mds.fyssagyro.model;

import com.google.gson.annotations.SerializedName;

public class MdsHeader {

    @SerializedName("Status")
    private int status;

    @SerializedName("Uri")
    private String uri;

    @SerializedName("Reason")
    private String reason;

    @SerializedName("Content-Length")
    private int contentLength;

    @SerializedName("Content-Type")
    private String contentType;

    @SerializedName("Location")
    private String location;

    @SerializedName("TaskId")
    private long taskId;

    public MdsHeader() {
    }

    public int getStatus() {
        return status;
    }

    public String getUri() {
        return uri;
    }

    public String getReason() {
        return reason;
    }

    public int getContentLength() {
        return contentLength;
    }

    public String getContentType() {
        return contentType;
    }

    public String getLocation() {
        return location;
    }

    public long getTaskId() {
        return taskId;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public void setUri(String uri) {
        this.uri = uri;
    }

    public void setReason(String reason) {
        this.reason = reason;
    }

    public void setContentLength(int contentLength) {
        this.contentLength = contentLength;
    }

    public void setContentType(String contentType) {
        this.contentType = contentType;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public void setTaskId(long taskId) {
        this.taskId = taskId;
    }

    public boolean isSuccess() {
        return (status / 100) == 2;
    }

    @Override
    public String toString() {
        return "MdsHeader{" +
                "status=" + status +
                ", uri='" + uri + '\'' +
                ", reason='" + reason + '\'' +
                ", contentLength=" + contentLength +
                ", contentType='" + contentType + '\'' +
                ", location='" + location + '\'' +
                ", taskId=" + taskId +
                '}';
    }
}
