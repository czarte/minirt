#!/bin/bash

EXEC=../.././miniRT
SCENES_DIR=./parser_test_scenes
OK=0
FAIL=0

run_test() {
    local file=$1
    local expected=$2

    echo -n "Testing $file... "

    output=$($EXEC "$file" 2>&1)
    if echo "$output" | grep -q "$expected"; then
        echo "✅ OK"
        ((OK++))
    else
        echo "❌ FAIL"
        echo "Expected error: $expected"
        echo "Got: $output"
        ((FAIL++))
    fi
}

mkdir -p "$SCENES_DIR"

# === Test files ===
cat > "$SCENES_DIR/empty.rt" <<EOF
EOF

cat > "$SCENES_DIR/missing_camera.rt" <<EOF
A 0.2 255,255,255
L 10,10,10 0.5 255,255,255
EOF

cat > "$SCENES_DIR/multiple_cameras.rt" <<EOF
C 0,0,0 0,0,1 70
C 1,1,1 0,1,0 60
EOF

cat > "$SCENES_DIR/unknown_type.rt" <<EOF
C 0,0,0 0,0,1 70
A 0.2 255,255,255
X 0,0,0 1
EOF

cat > "$SCENES_DIR/bad_rgb.rt" <<EOF
C 0,0,0 0,0,1 70
A 0.2 255,255,255
L 10,10,10 0.5 255,255,255
sp 0,0,0 10 300,255,255
EOF

cat > "$SCENES_DIR/bad_orientation.rt" <<EOF
C 0,0,0 0,0,1 70
A 0.2 255,255,255
L 10,10,10 0.5 255,255,255
cy 0,0,0 0,2,0 10 10 255,255,255
EOF

cat > "$SCENES_DIR/bad_brightness.rt" <<EOF
L 0,0,0 2.0 255,255,255
C 0,0,0 0,0,1 70
EOF

cat > "$SCENES_DIR/negative_diameter.rt" <<EOF
C 0,0,0 0,0,1 70
sp 0,0,0 -5 255,255,255
EOF

cat > "$SCENES_DIR/negative_height.rt" <<EOF
C 0,0,0 0,0,1 70
cy 0,0,0 0,1,0 5 -10 255,255,255
EOF

# === Run tests ===
run_test "$SCENES_DIR/empty.rt" "Error: Scene is empty"
run_test "$SCENES_DIR/missing_camera.rt" "Error: Scene must contain exactly one camera (C)"
run_test "$SCENES_DIR/multiple_cameras.rt" "Error: Scene must contain exactly one camera (C)"
run_test "$SCENES_DIR/unknown_type.rt" "Error: Unknown identifier"
run_test "$SCENES_DIR/bad_rgb.rt" "RGB values must be"
run_test "$SCENES_DIR/bad_orientation.rt" "Orientation vector"
run_test "$SCENES_DIR/bad_brightness.rt" "Brightness must be"
run_test "$SCENES_DIR/negative_diameter.rt" "Sphere diameter"
run_test "$SCENES_DIR/negative_height.rt" "Cylinder height"

echo ""
echo "✅ Passed: $OK"
echo "❌ Failed: $FAIL"

exit $FAIL
