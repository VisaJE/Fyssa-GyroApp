package com.movesense.mds.fyssagyro.model;

/**
 * POJO that encapsulates any callback from MdsInternal
 */
public final class MdsCallback {
    private final int taskId;
    private final int mdsCallType;
    private final MdsHeader header;
    private final String body;

    public MdsCallback(int taskId, int mdsCallType, MdsHeader header, String body) {
        this.taskId = taskId;
        this.mdsCallType = mdsCallType;
        this.header = header;
        this.body = body;
    }

    public int getTaskId() {
        return taskId;
    }

    int getMdsCallType() {
        return mdsCallType;
    }

    public MdsHeader getHeader() {
        return header;
    }

    public String getBody() {
        return body;
    }
}
