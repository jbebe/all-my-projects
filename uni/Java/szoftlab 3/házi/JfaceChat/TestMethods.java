package hazi;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestMethods {

	@Test
	public void test() {
		assertTrue(true);
	}
	
	@Test
	public void testImagePanel(){
		@SuppressWarnings("unused")
		ImagePanel im = new ImagePanel(null);
	}
	
	@Test
	public void testSASL(){
		@SuppressWarnings("unused")
		CustomSASLDigestMD5Mechanism sasl = new CustomSASLDigestMD5Mechanism(null);
	}

}
